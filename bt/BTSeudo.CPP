// Solucion factible
void caminoBT(){
    if(tengoQuePodar()) {
        if(esSolucion()) {
            //almaceno la solucion
        } else {
            // recorrer todos mis movimientos
            if(movimientoEsValido()) {
                aplicoMovimiento()
                caminoBT();
                deshagoMovimiento()
            }
        }
    }
}

// Solucion factible 2.0
bool caminoBT(){
    if(tengoQuePodar()) {
        if(esSolucion()) {
            //almaceno la solucion
            return true;
        } else {
            // recorrer todos mis movimientos
            if(movimientoEsValido()) {
                aplicoMovimiento()
                if(caminoBT()){
                    return true;
                }
                deshagoMovimiento()
            }
        }
    }
}

// Optimizacion
void caminoBT(){
    if(tengoQuePodar()) {
        if(esSolucion()) {
            if(esMejorSolucion()){
                // la guardo en una variable
            }
        } else {
            // recorrer todos mis movimientos
            if(movimientoEsValido()) {
                aplicoMovimiento()
                caminoBT();
                deshagoMovimiento()
            }
        }
    }
}

// Enumeracion
void caminoBT(){
    if(tengoQuePodar()) {
        if(esSolucion()) {
            // la agrego a lista de soluciones
        } else {
            // recorrer todos mis movimientos
            if(movimientoEsValido()) {
                aplicoMovimiento()
                caminoBT();
                deshagoMovimiento()
            }
        }
    }
}

// EnumeracionOptimizacion
void caminoBT(){
    if(tengoQuePodar()) {
        if(esSolucion()) {
            if(esMejorQueSolucionesOptimasAnteriores()){
                // vacio la lista de soluciones
                // la agrego a lista de soluciones 
            } else if (esIgualQueSolucionesOptimasAnteriores()){
                // la agrego a lista de soluciones
            }
        } else {
            // recorrer todos mis movimientos
            if(movimientoEsValido()) {
                aplicoMovimiento()
                caminoBT();
                deshagoMovimiento()
            }
        }
    }
}