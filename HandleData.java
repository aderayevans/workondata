
public class HandleData {
	private String fullName;
	private String mssv;
	private Date born;
	private String hTown;
	private float avrPoint, gPA;
	
	public HandleData() {
		fullName = ("Quang");
		mssv = ("B1510210");
		born = new Date();
		hTown = ("An Giang");
		avrPoint = gPA = 0;
	}
	public HandleData(String fullName, String mssv, Date born, String hTown, float avrPoint, float gPA) {
		this.fullName = fullName;
		this.mssv = mssv;
		this.born = born;
		this.hTown = hTown;
		this.avrPoint = avrPoint;
		this.gPA = gPA;
	}
	public HandleData(String x) {
		fullName = cutFName(x);
		mssv = cutMSSV(x);
		born = cutDate(x);
		hTown = cutHTown(x);
		avrPoint = cutAVR(x);
		gPA = cutGPA(x);
	}
	public String cutFName(String x) {
		char[] tmp = new char[50];
		String str = new String();
		x.getChars(4,33,tmp,0);
		str = String.copyValueOf(tmp);
		str = str.trim();
		str = String.format("%-30s", str);
		return str;
	}
	public String cutMSSV(String x) {
		char[] tmp = new char[50];
		String str = new String();
		x.getChars(34,42,tmp,0);
		str = String.copyValueOf(tmp);
		str = str.trim();
		str = String.format("%-10s", str);
		return str;
	}
	public Date cutDate(String x) {
		char[] tmp = new char[50];
		String str = new String();
		x.getChars(44,46,tmp,0);
		str = String.copyValueOf(tmp);
		str = str.trim();
		int a = Integer.parseInt(str);
		
		x.getChars(47,49,tmp,0);
		str = String.copyValueOf(tmp);
		str = str.trim();
		int b = Integer.parseInt(str);
		
		x.getChars(50,54,tmp,0);
		str = String.copyValueOf(tmp);
		str = str.trim();
		int c = Integer.parseInt(str);
		
		Date date = new Date(a,b,c);
		return date;
	}
	public String cutHTown(String x) {
		char[] tmp = new char[50];
		String str = new String();
		x.getChars(56,71,tmp,0);
		str = String.copyValueOf(tmp);
		str = str.trim();
		str = String.format("%-15s", str);
		return str;
	}
	public float cutAVR(String x) {
		char[] tmp = new char[50];
		String str = new String();
		x.getChars(71,81,tmp,0);
		str = String.copyValueOf(tmp);
		str = str.trim();
		float a = Float.parseFloat(str);
		return a;
	}
	public float cutGPA(String x) {
		char[] tmp = new char[50];
		String str = new String();
		x.getChars(81,84,tmp,0);
		str = String.copyValueOf(tmp);
		str = str.trim();
		float a = Float.parseFloat(str);
		return a;
	}
	
	public String takeFName() {
		return fullName;
	}
	public String takeMSSV() {
		return mssv;
	}
	public String takeDate() {
		String day = String.format("%02d", born.getDay());
		String month = String.format("%02d", born.getMonth());
		String str = (day + "/" + month + "/" + born.getYear());
		return str;
	}
	public String takeHTown() {
		return hTown;
	}
	public String takeAVR() {
		String str = String.format("%-10s", avrPoint);
		return str;
	}
	public String takeGPA() {
		return Float.toString(gPA);
	}

	
}
