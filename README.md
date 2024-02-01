# Threads_Multi-Mono

1. Ejecutar los siguientes casos y justificar su comportamiento:
a. ./practica1 (multicore)
Todos los threads cumplen sus periodos y ejecutan en el tiempo de coste.
b. ./practica1 (monocore)
Todos los threads se pasan del tiempo de coste, por lo que no son capaces de cumplir sus periodos. Al
ejecutarse con una sola cpu no somos capaces de cumplir con la planificación.
c. ./practica1 (monocore) + stress
Igual que en el apartado b, con una sola cpu no somos capaces de cumplir con la planificación y mucho
menos si la estresamos.
d. ./practica1 (multicore) + stress
En este apartado solo en algunos ordenadores funciona, por lo que podríamos deducir que necesitamos un
ordenador en buen estado y con un funcionamiento óptimo para poder cumplir los tiempos de coste.
Es cierto, que bajando nuestro bucle for dependiendo de cada ordenador, funciona en todos.
2. ¿En qué casos de ejecución (nombrados anteriormente) el sistema es capaz de
cumplir las restricciones temporales (tanto tiempo de cómputo como
periodicidad)?
Solo se cumplen ejecutándolo en un sistema multicore sin estrés o en un sistema multicore con estres
computacional en como máximo 3 cpus.
3. ¿Qué número mínimo de cpus se necesitan para que tu programa ejecute
correctamente sin fallos de restricciones temporales? Usa el comando taskset
para comprobarlo.
Tras varias comprobaciones, necesitamos 3 cpus como mínimo para poder cumplir los requisitos temporales.
4. ¿Qué solución se podría proponer para cumplir plazos estrictos temporales de
periodicidad en la ejecución de los threads utilizando la configuración actual que
tienen los ordenadores del laboratorio?
Aumentar el periodo no nos serviría ya que solo funcionaría en ciertos casos, nosotros queremos que
funcione en cualquier escenario. Suponiendo que usamos los ordenadores de los laboratorios, podríamos
cambiar el orden de prioridad de nuestros threads, así ejecutarían antes que todos esos procesos que puedan
causar estrés o incluso con cpus bloqueadas. Aumentarles la prioridad (bajar el número de prioridad) nos
permitiría cumplir los requisitos temporales.
