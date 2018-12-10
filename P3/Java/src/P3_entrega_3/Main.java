package P3_entrega_3;
import static P3_entrega_3.Etc.*;
import P3_entrega_3.Tabulation;
public class Main {
    static int[] matrix;
    
    static long min_operations_tabulation=0L;
    static double timer_tabulation=0.;
    
    static Memoization init_memoization;
    static long min_operations_memoization=0L;
    static double timer_memoization=0.;
    
    public static void main(String[] args) {
        
        String [] args_mio = new String [4];
        args_mio[0]="-f";
        args_mio[1]="../esclavo/pruebas.txt";
        args_mio[2]="-tab";
        args_mio[3]="-t";
        //args_mio[4]="-do";
        //args_mio[5]="-di";
        //args_mio[6]="-mem";
        
        GetParam(args_mio); // leemos los parametros introducidos al programa
        if(di_flag)Input(); // debug input
        if(!do_flag && !t_flag)System.exit(0);
        
        prepareReader(); // preparamos un buffer que nos permitira leer de readMatrix()
            
        while((matrix = readMatrix())!= null){          
            if(tab_flag){ // -tab ?
                if(t_flag)ComienzaTimer(); // comenzamos a contar el tiempo de ejecucion
                min_operations_tabulation = Tabulation.MatrixChainOrder(matrix, matrix.length); // algoritmo tabulation
                if(t_flag)timer_tabulation=ParaTimer(); // calculamos el tiempo de ejecucion
            }
            
            if(mem_flag){ // -mem ?
                if(t_flag)ComienzaTimer(); // comenzamos a contar el tiempo de ejecucion
                init_memoization = new Memoization(matrix); // inicializamos el map que usa la memoization
                min_operations_memoization = init_memoization.MatrixChainOrder(1, matrix.length-1); // algoritmo memoization
                init_memoization.clean(); // reseteamos el map que usa la memoization
                if(t_flag)timer_memoization=ParaTimer(); // calculamos el tiempo de ejecucion
            }
            
            if(do_flag || t_flag)Output(matrix, min_operations_tabulation, timer_tabulation, min_operations_memoization, timer_memoization); // debug output/timer
        }
    }
}
