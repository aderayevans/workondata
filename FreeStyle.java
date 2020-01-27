import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;

public class FreeStyle {
	private static HandleData[] ds = new HandleData[9];
	
	
	public static void main(String[] args) {
		readFile();
        	writeFile();
	}
	public static void readFile() {
		BufferedReader br = null;
        try {   
            br = new BufferedReader(new FileReader("C:\\Users\\Quang\\Desktop\\Data.out"));
            System.out.println("read()");
            String line;
            int i=0;
            while((line = br.readLine()) != null) {  
                System.out.println(line);
                ds[i] = new HandleData(line);
                i++;
            }
        } catch (IOException e) {
            e.printStackTrace();
        } finally {
            try {
                br.close();
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
	}
	public static void writeFile() {
		FileWriter fw = null;
        try {
            fw = new FileWriter(new File("C:\\Users\\Quang\\Desktop\\Data.outf"));
            
            for (int i=0; i<9; i++) {
            	fw.write("  " + (i+1) + " " + ds[i].takeFName() + ds[i].takeMSSV() + ds[i].takeDate() +"  " + ds[i].takeHTown() + ds[i].takeAVR() + ds[i].takeGPA() + "\n");
            }
        } catch (IOException e) {
        	  e.printStackTrace();
        } finally {
        	try {
                fw.close();
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
	}
}
