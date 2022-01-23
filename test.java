import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;

public class test{
    public static void main(String[] args) {
        try{
            BufferedReader myout = new BufferedReader(new FileReader("./tests/tests/myout"));
            BufferedReader out = new BufferedReader(new FileReader("./tests/tests/out"));

            for (int i = 1; i < 10001; i++){
                String myoutLine = myout.readLine();
                String outLine = out.readLine();

                if (!myoutLine.equals(outLine) && !myoutLine.equals("0")){
                    System.out.println(i);
                }
            }

            out.close();
            myout.close();

        } catch(IOException e){ e.printStackTrace(); }
    }
}