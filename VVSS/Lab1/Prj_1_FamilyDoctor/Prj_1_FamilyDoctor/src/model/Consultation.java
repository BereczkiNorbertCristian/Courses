package model;

import java.util.ArrayList;
import java.util.List;

public class Consultation {
	private String consID;
	private String PatientSSN;
	private String diag;
	private List<String> meds;
	private String consultation_date;
	
	public Consultation() 
	{ 
		this.consID = new String();
		this.PatientSSN = new String();
		this.diag = new String();
		this.meds = new ArrayList<String>();
		this.consultation_date = new String();
	};
	
	public Consultation (String consID, String PatientSSN, String diag, List<String> meds, String date)
	{
		this.consID = consID;
		this.PatientSSN = PatientSSN;
		this.diag = diag;
		this.meds = meds;
		this.consultation_date = date;
	}
	
	public String getConsID() {
		return consID;
	}
	public void setConsID(String v_consID) {
		consID = v_consID;
	}
	
	public String getPatientSSN() {
		return PatientSSN;
	}
	public void setPatientSSN(String patientSSN) {
		PatientSSN = patientSSN;
	}
	public String getDiag() {
		return diag;
	}
	public void setDiag(String diag) {
		this.diag = diag;
	}
	public List<String> getMeds() {
		return meds;
	}
	public void setMeds(List<String> meds) {
		this.meds = meds;
	}
	public String getConsultation_date() {
		return consultation_date;
	}
	public void setConsultation_date(String consultation_date) {
		this.consultation_date = consultation_date;
	}
	
	public String toString()
	{
		String res;
		 res = consID + "," + PatientSSN + ',' + diag + ",";
		 
		 for (int i = 0; i<meds.size()-1;i++)
		 {
			 res = res + meds.get(i) + "+";
		 }
		 
		 res = res.substring(0, res.length()-1);
		 
		 res = res + "," + consultation_date;
		 
		 return res;
		
	}

}
