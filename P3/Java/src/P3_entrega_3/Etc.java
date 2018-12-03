package P3_entrega_3;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.text.DecimalFormat;
import java.util.logging.Level;
import java.util.logging.Logger;


public class Etc {
    // Flags
    public static boolean f_flag=false, t_flag=false, di_flag=false, do_flag=false, tab_flag=false, mem_flag=false;
    public static String path="";

    
    /*
      GetParam(String[]args): Lee los parametros pasados al programa, por medio
      del array "args". De esta forma se identifican y se activan los flags
      correspondientes, que permiten activar unas operaciones u otras.
    */
    public static void GetParam(String [] args){
        if (args.length==0) {
            System.err.println("Sintaxis: main -f file [-di] [-do|-t] [-mem|-tab]");
            System.exit(1);
        }
        for (int i = 0; i < args.length; i++) {
            if(args[i].equals("-f")){
                f_flag=true;
                path=args[i+1];
            }
            if(args[i].equals("-t"))t_flag=true;
            if(args[i].equals("-di"))di_flag=true;
            if(args[i].equals("-do"))do_flag=true;
            if(args[i].equals("-tab"))tab_flag=true;
            if(args[i].equals("-mem"))mem_flag=true;
        }
        if (!f_flag){
            System.err.println("Ha de introducir un fichero");
            System.exit(1);
        }
        if (!tab_flag && !mem_flag){
            System.err.println("Error: si se ha escogido -do o -t, se ha de "
                    + "especificar -tab ('tabulation') o/y -mem ('memoization')");
            System.exit(1);
        }
    }
    
    
    /*
      Input(): Es llamado cuando se usa la opcion -di. Tiene la funcion de mostrar
      por pantalla el contenido del fichero pasado al programa por parametros.
    */
    public static void Input(){
        try{
            prepareReader();
            String linea="";
            while((linea = br.readLine()) != null){
                System.out.println(linea);
            }
            br.close();
            System.out.println("-------------------------------------------------");
        }catch (Exception e){
            System.err.println("Error al leer del buffer");
        }
    }
    
    
    private static BufferedReader br;
    
    public static void prepareReader(){
        try{
            FileReader fichero = new FileReader(path); 
            br = new BufferedReader(fichero);// cargamos el fichero en un buffer
        } catch (FileNotFoundException ex) {
            System.err.println("Error al leer input");
        }
        
    }
    
    public static int [] readMatrix(){
        int[] matrix=null;
        try {
            String linea;
            if((linea = br.readLine()) != null){
                String[] split = linea.split(",");
                matrix = new int[split.length];
                for (int i = 0; i < matrix.length; i++) {
                    matrix[i] = Integer.parseInt(split[i]);
                }
            }else{
                br.close();
            }
        } catch (IOException ex) {
            System.err.println("Error al leer del buffer");
        }
        return matrix;
    }
    
    // Variables para medir el tiempo
    private static long timer;


    /*
      ComienzaTimer(): Toma el valor del instante actual y lo guarda en "timer".
    */
    public static void ComienzaTimer(){
        timer = System.nanoTime();
    }


    /*
      ParaTimer(): Calcula el tiempo transcurrido desde el momento en que se
      asigno un valor a "timer" hasta el momento actual y se guarada en la variable
      "tiempoTranscurrido".
    */
    public static double ParaTimer(){
        return (System.nanoTime() - timer)/(1000000000.);
    }
    
    
    /*
      Output
    */
    public static void Output(int [] matrix, long min_operations_tabulation, double timer_tabulation,
                                             long min_operations_memoization, double timer_memoization){
        
        System.out.println("nº matrices => " + (matrix.length -1));
        
        if(do_flag){
            if(tab_flag)System.out.println("minimo de operaciones (tabulation) => " + min_operations_tabulation);
            if(mem_flag)System.out.println("minimo de operaciones (memoization) => " + min_operations_memoization);
        }
        
        if(t_flag){
            DecimalFormat df = new DecimalFormat("#.######");
            if(tab_flag)System.out.println("Tiempo (tabulation) => " + df.format(timer_tabulation) + "s");
            if(mem_flag)System.out.println("Tiempo (memoization) => " + df.format(timer_memoization) + "s");
        }
        
        System.out.println("-------------------------------------------------");
    }
}
