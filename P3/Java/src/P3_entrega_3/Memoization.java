package P3_entrega_3;

import java.util.HashMap;
import java.util.Map;

public class Memoization{

  private Map<String, Long> mem = new HashMap<>();
  private long inf = Long.MAX_VALUE;
  private int [] matrix;


  public Memoization(int [] p){

    int n = p.length;
    matrix = p;
    long cero = 0L;

    for(int i = 1; i < n; i++){
      for(int j = 1; j < n; j++){
        String key = i + "," + j;
        if(i == j) mem.put(key, cero);
        else mem.put(key, inf);
      }

    }
  }

  public void clean(){
    mem.clear();
  }

  public long MatrixChainOrder(int i, int j){

    String key = i + "," + j;

    if(mem.get(key) < inf) return mem.get(key);
    else{
      for (int k = i; k < j ; k++) {
        long q = q = MatrixChainOrder(i, k) +
		MatrixChainOrder(k + 1, j) +
		matrix[i - 1] * matrix[k] * matrix[j];
		
        if (q < mem.get(key)) mem.put(key,q);
      }
    }
    return mem.get(key);
  }
}
