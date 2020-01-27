
public class Date {
	private int dd, mm, yyyy;
	
	public Date() {
		dd = 26;
		mm = 11;
		yyyy = 1997;
	}
	public Date(int d, int m, int y) {
		dd = d;
		mm = m;
		yyyy = y;
	}
	
	public int getDay() {
		return dd;
	}
	public int getMonth() {
		return mm;
	}
	public String getYear() {
		return Integer.toString(yyyy);
	}
}
