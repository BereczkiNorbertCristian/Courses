package model;

public class Patient {
	private String Patient_ID;
	private String Name;
	private String SSN;
	private String address;
	private int consNum;
	
	/** Constructors */
	
	public Patient() {};
	
	public Patient(String Name, String SSN, String address) 
	{
			this.Patient_ID = SSN;
			this.Name = Name;
			this.SSN = SSN;
			this.address = address;	
			this.consNum = 0;
	}
	
	/** Getters and setters */
	public String getPatient_ID() {
		return Patient_ID;
	}
	public void setPatient_ID(String patient_ID) {
		Patient_ID = patient_ID;
	}
	public String getName() {
		return Name;
	}
	public void setName(String name) {
		Name = name;
	}
	public String getSSN() {
		return SSN;
	}
	public void setSSN(String sSN) {
		SSN = sSN;
	}
	public String getAddress() {
		return address;
	}
	public void setAddress(String address) {
		this.address = address;
	}
	public void setConsNum(int num)
	{
		this.consNum = num;
	}
	public int getConsNum()
	{
		return this.consNum;
	}
	
	/** Others */
	public String toString() {
	    return Name + "," + SSN + "," +address;
	//	return Name + "," + consNum;
	}
}
