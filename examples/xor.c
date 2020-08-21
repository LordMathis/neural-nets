#include "../lib/network.h"
#include "../lib/functions.h"

int main() {
    const int layers[] = {2,1};
    double (*act_sigmoid_ptr)(double) = &act_sigmoid;

    Network *xor_network = create_network(2, 2, layers, act_sigmoid_ptr);

    
}