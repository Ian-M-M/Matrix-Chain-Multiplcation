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

if flagDi == 1:
    print "Nombre del fichero: " + path + "\n"
    for linea in fichero:
        print linea
    etc.cerrarFichero(fichero)

if (flagT == 0) and (flagDi == 0) and (flagDo == 0):
    print "Para que el programa funciones correctemente use alguno de los comandos disponibles, 'python main.py -h'"
    exit(1)

if (flagDo == 0 or flagT == 0) and flagTab == 0 and flagMem == 0 and flagDi == 0:
    print "Para mostrar el output ha de indicar que metodo quiere aplicar, indique -mem o -tab"
    exit(1)

if flagDo == 1 or flagT == 1:

    if flagDi == 1:
        fichero = etc.abrirFichero(path)

    for linea in fichero:

        arr = etc.lstStringToInt(linea)
        size = len(arr)

        if size < 3:
            print "El array no es valido, minimo necesito 3 elementos"
        else:
            minTab = 0
            minMem = 0
            timeTab = 0
            timeMem = 0

            if flagMem == 1:
                memoization.clean()
                memoization.init(arr)

            print "Size =>", size
            print ""

            if flagTab == 1:

                print "Computing Tabulation ..."

                if flagT == 1: etc.time.clock()

                minTab = tabulation.MatrixChainOrder(arr, size)

                if flagT == 1: timeTab = etc.time.clock()

            if flagMem == 1:

                print "Computing Memoization ..."

                if flagT == 1: etc.time.clock()

                minMem = memoization.MatrixChainOrder(1, size-1)

                if flagT == 1: timeMem = etc.time.clock()

            print ""

            if flagDo == 1:
                if flagTab == 1: print "Min operations (Tabulation) => " + str(minTab)
                if flagMem == 1: print "Min operations (Memoization) => " + str(minMem)
            if flagT == 1:
                if flagTab == 1: print "Time (Tabulation) => " + str(timeTab)
                if flagMem == 1: print "Time (Memoization) => " + str(timeMem)

        print "--------------------------------------------------------"

etc.cerrarFichero(fichero)
