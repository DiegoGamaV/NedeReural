#include "layer.h"

Layer hidden;

Layer output;
void feedfoward(Narray activation){

    Narray hidden_result = hidden.activate(activation);

    output.activate(hidden_result);
}