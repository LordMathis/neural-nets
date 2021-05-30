# NeuralNets

Small neural network library written in C from scratch.

## Features

* Mini-batch gradient descent
* Mean squared error
* Cross-entropy cost
* Sigmoid activation
* L2 regularization (weight decay)
* Momentum

## Usage

Run tests

```
make test
./build/test
```

Train xor

```
make xor
./build/xor
```

Train MNIST

* Download the dataset, convert to csv and save to `resources` folder

```
make mnist
./build/mnist
```

## MNIST Results

~97% validation accuracy after around 10 epochs
* sigmoid activation and cross entropy cost
* single hidden layer with 50 hidden neurons
* learning rate: 0.1
* batch size: 10
* momentum 0.9
* L2 lambda: 0.09

See `examples/mnist.c` for details. For MNIST digits classification you need to have the dataset converted to csv format.