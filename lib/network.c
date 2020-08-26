#include "layer.h"
#include "matrix.h"
#include "network.h"
#include "utils.h"
#include <stdlib.h>
#include <stdio.h>

Network* create_network(int input_size, int num_layers, int layers[], Activation *activation)
{
    Network *network = (Network *) malloc (sizeof (Network));
    network->num_layers = num_layers;

    network->layers = (Layer **) malloc (sizeof (Layer*) *num_layers);
    int prev_layer_size = input_size;
    for (int i = 0; i < num_layers; i++)
    {
        network->layers[i] = create_layer(layers[i], prev_layer_size, activation);
        prev_layer_size = layers[i];
    }
    
    return network;
}

void print_network(Network *network)
{
    for (int i = 0; i < network->num_layers; i++)
    {
        printf("Layer %d\n", i);
        print_matrix(network->layers[i]->weights);
    }    
}

int delete_network(Network *network)
{
    for (int i = 0; i < network->num_layers; i++)
    {
        delete_layer(network->layers[i]);
    }

    free(network->layers);
    free(network);
    network = NULL;

    return 0;
}

Matrix* predict(Network *network, Matrix *input)
{
    Matrix *layer_input = input;
    for (int i = 0; i < network->num_layers; i++)
    {
        Layer *layer = network->layers[i];
        int res = layer_compute(layer, layer_input);
        if (res < 0)
        {
            log_exception(__func__, "Exception during prediction");
        }
        layer_input = layer->neurons_act;
    }
    
    return layer_input;
}

static int init_training(
    Network *network,
    Matrix **deltas,
    Matrix **temp_deltas,
    Matrix **delta_weights,
    Matrix **temp_delta_weights,
    Matrix **transposed_weights,
    Matrix **delta_bias)
{
    for (int i = 0; i < network->num_layers; i++)
    {
        int rows = network->layers[i]->weights->rows;
        int cols = network->layers[i]->weights->cols;

        delta_weights[i] = create_matrix(rows, cols, NULL);
        temp_delta_weights[i] = create_matrix(rows, cols, NULL);

        if (i>0)
        {
            transposed_weights[i-1] = create_matrix(cols, rows, NULL);
            transpose(network->layers[i]->weights, transposed_weights[i-1]);
        }

        int bias_rows = network->layers[i]->bias->rows;
        int bias_cols = network->layers[i]->bias->cols;

        delta_bias[i] = create_matrix(bias_rows, bias_cols, NULL);
        deltas[i] = create_matrix(bias_rows, bias_cols, NULL);

        if (i>0)
        {
            temp_deltas[i-1] = create_matrix(cols, bias_cols, NULL);
        }
    }

    return 0;
}

static int backpropagate(
    Network *network,
    Matrix *input,
    Matrix **deltas,
    Matrix **temp_deltas,
    Matrix **delta_weights,
    Matrix **temp_delta_weights,
    Matrix **transposed_weights,
    Matrix **delta_bias)
{
    int res;
    Layer *layer;
    Matrix *prev_act;

    for (int l = network->num_layers - 2; l >= 0; l--)
    {
        layer = network->layers[l];

        if (l == 0)
        {
            prev_act = input;
        }
        else
        {
            prev_act = network->layers[l-1]->neurons_act;
        }
        
        // Compute new delta
        res = 0;
        res += apply(layer->neurons, NULL, layer->activation->fn_der);
        res += multiply(transposed_weights[l], deltas[l+1], temp_deltas[l]); // Transposed weights array is 1 shorter than matrix length
        res += hadamard(temp_deltas[l], layer->neurons, deltas[l]);
        if (res < 0)
        {
            log_exception(__func__, "Exception during delta calculation");
            return res;
        }

        // printf("Layer %d\n", l);
        // print_matrix(layer->neurons);
        // printf("\n");
        // print_matrix(temp_deltas[l]);
        // printf("\n");
        // print_matrix(deltas[l]);
        // printf("\n");

        // Compute delta weights
        res = 0;
        res += multiply_transposed(deltas[l], prev_act, temp_delta_weights[l]);
        res += add(delta_weights[l], temp_delta_weights[l]);
        if (res < 0)
        {
            log_exception(__func__, "Exception during delta weights calculation");
            return res;
        }

        // Compute delta bias
        res = add(delta_bias[l], deltas[l]);
        if (res < 0)
        {
            log_exception(__func__, "Exception during delta bias calculation");
            return res;
        }

        // print_matrix(deltas[l]);
        // printf("\n");
        // print_matrix(prev_act);
        // printf("\n");
        // print_matrix(temp_delta_weights[l]);
        // printf("\n");
    }      
}

static void cleanup(
    int network_length,
    Matrix **deltas,
    Matrix **temp_deltas,
    Matrix **delta_weights,
    Matrix **temp_delta_weights,
    Matrix **transposed_weights,
    Matrix **delta_bias)
{
        // Cleanup
    for (int i = 0; i < network_length; i++)
    {
        delete(deltas[i]);
        delete(delta_weights[i]);
        delete(temp_delta_weights[i]);
        delete(delta_bias[i]);

        if (i != network_length - 1) {
            delete(transposed_weights[i]);
            delete(temp_deltas[i]);
        }
    }
    free(deltas);
    free(temp_deltas);
    free(delta_weights);
    free(temp_delta_weights);
    free(transposed_weights);
    free(delta_bias);
}

static int reset(
    Network *network,
    Matrix **deltas,
    Matrix **temp_deltas,
    Matrix **delta_weights,
    Matrix **temp_delta_weights,
    Matrix **transposed_weights,
    Matrix **delta_bias)
{
    int res = 0;
    for (int i = 0; i < network->num_layers; i++)
    {
        res += reset_matrix(deltas[i]);
        res += reset_matrix(delta_weights[i]);
        res += reset_matrix(temp_delta_weights[i]);
        res += reset_matrix(delta_bias[i]);

        if (i != network->num_layers - 1) {
            res += reset_matrix(transposed_weights[i]);
            res += reset_matrix(temp_deltas[i]);
        }

        if (i != 0)
        {
            res += transpose(network->layers[i]->weights, transposed_weights[i-1]);
        }

        if (res < 0)
        {
            log_exception(__func__, "Exception during training temp objects reset");
            return res;
        }
    }    
}

int train(Network *network, Matrix **input_dataset, Matrix** input_labels, int dataset_size, int epochs, double learning_rate)
{
    // Allocate all the memory
    Matrix **delta_weights = (Matrix **) malloc (sizeof (Matrix*) * network->num_layers);
    Matrix **temp_delta_weights = (Matrix **) malloc (sizeof (Matrix*) * network->num_layers);

    Matrix **delta_bias = (Matrix **) malloc (sizeof (Matrix*) * network->num_layers);

    Matrix **deltas = (Matrix **) malloc (sizeof (Matrix*) * network->num_layers);

    Matrix **temp_deltas = (Matrix **) malloc (sizeof (Matrix*) * network->num_layers -1);
    Matrix **transposed_weights = (Matrix **) malloc (sizeof (Matrix*) * network->num_layers - 1);

    init_training(
        network,
        deltas,
        temp_deltas,
        delta_weights,
        temp_delta_weights,
        transposed_weights,
        delta_bias
    );

    Matrix *prediction;
    Matrix *target;

    int L =  network->num_layers - 1;
    Layer *last_layer = network->layers[L];

    int res = 0;
    int epoch = 0;

    while (epoch < epochs) {

        // printf("Epoch: %d/%d\n\n", epoch+1, epochs);

        for (int i = 0; i < dataset_size; i++)
        {
            // printf("Example:\n");
            // print_matrix(input_dataset[i]);
            // printf("\n");

            prediction = predict(network, input_dataset[i]);
            target = input_labels[i];

            if (predict == NULL)
            {
                log_exception(__func__, "Exception during prediction");
                return -1;
            }

            // Calculate initial delta
            res = 0;
            res += subtract(prediction, target);
            res += apply(last_layer->neurons, NULL, last_layer->activation->fn_der);
            res += hadamard(prediction, last_layer->neurons, deltas[L]);
            if (res < 0)
            {
                log_exception(__func__, "Exception during output delta calculation");
                return res;
            }

            // Update delta weights
            res = 0;
            res += multiply_transposed(deltas[L], network->layers[L - 1]->neurons_act, temp_delta_weights[L]);
            res += add(delta_weights[L], temp_delta_weights[L]);
            if (res < 0)
            {
                log_exception(__func__, "Exception during output delta weights calculation");
                return res;
            }

            // printf("Temp delta weights:\n");
            // print_matrix(deltas[L]);
            // printf("\n");
            // print_matrix(network->layers[L - 1]->neurons_act);
            // printf("\n");
            // print_matrix(temp_delta_weights[L]);

            // Update delta biases
            res = add(delta_bias[L], deltas[L]);
            if (res < 0)
            {
                log_exception(__func__, "Exception during output delta bias calculation");
                return res;
            }

            backpropagate(
                network,
                input_dataset[i],
                deltas,
                temp_deltas,
                delta_weights,
                temp_delta_weights,
                transposed_weights,
                delta_bias
            );
        }

        // TODO: Adjust weights
        double eta = -1 * (learning_rate/dataset_size);
        for (int i = 0; i < network->num_layers; i++)
        {   
            scalar_multiply(delta_weights[i], eta);
            add(network->layers[i]->weights, delta_weights[i]);

            scalar_multiply(delta_bias[i], eta);
            add(network->layers[i]->bias, delta_bias[i]);
        }
        
        reset(
            network,
            deltas,
            temp_deltas,
            delta_weights,
            temp_delta_weights,
            transposed_weights,
            delta_bias
        );
        
        epoch++;   
    }

    cleanup(
        network->num_layers,
        deltas,
        temp_deltas,
        delta_weights,
        temp_delta_weights,
        transposed_weights,
        delta_bias
    );
}
