#include "trainingExample.h"

TrainingExample::TrainingExample(Narray &data, unsigned int _representedValue){

	// Guardando os valores do struct;
	representedValue = _representedValue;
	imageData = data;

}

TrainingExample::TrainingExample(){
	// TODO
}