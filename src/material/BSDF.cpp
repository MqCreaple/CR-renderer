#include "material/BSDF.h"
#include "material/DiffuseBSDF.h"

const BSDF* BSDF::DEFAULT = new DiffuseBSDF();