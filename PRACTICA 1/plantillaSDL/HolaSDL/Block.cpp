#include "Block.h"

void Block::hit()
{
	// El bloque sera obstaculo si se choca desde arriba o lateral.
	// Si Mario toca desde abajo:
	//    - Si es tipo LADRILLO y Mario es GRANDE el bloque se destruye.
	//    - Si es tipo SORPRESA/OCULTO, Mario es GRANDE y la accion es POTENCIADOR, aparece un Superchampi y lo convierte en tipo VACIO.
}
