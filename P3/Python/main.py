import etc
import tabulation
import memoization

flagT = 0
flagF = 0
flagDi = 0
flagDo = 0
flagMem = 0
flagTab = 0

args, flagF, flagT, flagDi, flagDo, flagMem, flagTab = etc.ProcesaArgumentos(flagT, flagF, flagDi, flagDo, flagMem,
                                                                             flagTab)

path = args.file

fichero = etc.abrirFichero(path)
# Opcion de mostrar el contenido del archivo que se pasa por parametro
if flagDi == 1:
    print "File name: " + path + "\n"
    for linea in fichero:
        print linea
    etc.cerrarFichero(fichero)

# Comprobamos errores
if (flagT == 0) and (flagDi == 0) and (flagDo == 0):
    print "Para que el programa funciones correctemente use alguno de los comandos disponibles, 'python main.py -h'"
    exit(1)

# Comprobamos errores
if (flagDo == 0 or flagT == 0) and flagTab == 0 and flagMem == 0 and flagDi == 0:
    print "Para mostrar el output ha de indicar que metodo quiere aplicar, indique -mem o -tab"
    exit(1)

if flagDo == 1 or flagT == 1:

    if flagDi == 1:
        fichero = etc.abrirFichero(path)

    for linea in fichero:

        arr = etc.lstStringToInt(linea)
        size = len(arr)
        # Necesitamos al menos 2 matrices
        if size < 3:
            print "El array no es valido, minimo necesito 3 elementos"
        else:
            # minimo de operaciones y tiempo de tabulation y memoization
            minTab = 0
            minMem = 0
            timeTab = 0
            timeMem = 0
            # Inicializamos el dictionary que vamos a usar para resolver por memoization
            if flagMem == 1:
                memoization.clean()
                memoization.init(arr)

            print "n matrices => " + str(size-1)

            if flagTab == 1:
                # Primera medida de tiempo
                if flagT == 1: etc.time.clock()

                minTab = tabulation.MatrixChainOrder(arr, size)
                # Segunda medida de tiempo
                if flagT == 1: timeTab = etc.time.clock()

            if flagMem == 1:
                # Primera medida de tiempo
                if flagT == 1: etc.time.clock()

                minMem = memoization.MatrixChainOrder(1, size-1)
                # Segunda medida de tiempo
                if flagT == 1: timeMem = etc.time.clock()
            # Creamos el output
            if flagDo == 1:
                if flagTab == 1: print "minimo de operaciones (Tabulation) => " + str(minTab)
                if flagMem == 1: print "minimo de operaciones (Memoization) => " + str(minMem)
            if flagT == 1:
                if flagTab == 1: print "Tiempo (Tabulation) => " + str(timeTab) + " s"
                if flagMem == 1: print "Tiempo (Memoization) => " + str(timeMem) + " s"
        print "--------------------------------------------------------"

etc.cerrarFichero(fichero)
