package repository;


import java.io.BufferedReader;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.List;

import model.Consultation;
import model.Patient;


public class Repository {
	
	private String patients; // list of patients
	private String consultations; // list of consultation

	private ArrayList<Consultation> consultationList;
	private ArrayList<Patient> patientList;
	
	public Repository(String patients, String consultations) 
	{
		this.patients = patients;
		this.consultations = consultations;
		
		consultationList = new ArrayList<Consultation>();
		patientList = new ArrayList<Patient>();
	}
	
	public void cleanFiles()
	{
		FileWriter fw;
		try {
			fw = new FileWriter(patients);
			PrintWriter out=new PrintWriter(fw);
			out.print("");
			out.close();
		} catch (IOException e) {
			e.printStackTrace();
		}
		
		FileWriter fwc;
		try {
			fwc = new FileWriter(consultations);
			PrintWriter out=new PrintWriter(fwc);
			out.print("");
			out.close();
		} catch (IOException e) {
			e.printStackTrace();
		}

		consultationList = new ArrayList<Consultation>();
		patientList = new ArrayList<Patient>();
	}
	
	public String[] getPatientsFromFile() throws IOException
	{
		int n = 0;
		BufferedReader in = new BufferedReader(new FileReader(patients));
		while ((in.readLine()) != null) {
			n++;
		}
		in.close();
		
		String[] la=new String[n];
		String s = new String();
		int i = 0;
		in = new BufferedReader(new FileReader(patients));
		while ((s=in.readLine()) != null) {
			la[i] = s;
			i++;
		}
		in.close();
		return la;
	}
	
	public String[] getConsultationsFromFile() throws IOException
	{
		int n = 0;
		BufferedReader in = new BufferedReader(new FileReader(consultations));
		while ((in.readLine()) != null) {
			n++;
		}
		in.close();
		
		String[] la=new String[n];
		String s = new String();
		int i = 0;
		in = new BufferedReader(new FileReader(consultations));
		while ((s=in.readLine()) != null) {
			la[i] = s;
			i++;
		}
		in.close();
		return la;
	}
	
	public List<Patient> getPatientList()
	{
		List<Patient> lp = new ArrayList<Patient>();
		try {
			String[] tokens = getPatientsFromFile();
			
			String tok = new String();
			String[] pat;
			int i = 0;
			while (i < tokens.length)
			{ 
				tok = tokens[i];
				pat = tok.split(",");
				lp.add(new Patient(pat[0],pat[1],pat[2]));	
				i = i + 1;
			}
			
		} catch (IOException e) {
			e.printStackTrace();
		}
		
		return lp;	
	}
	
	public List<Consultation> getConsultationList()
	{
		List<Consultation> lp = new ArrayList<Consultation>();
		try {
			String[] tokens = getConsultationsFromFile();
			
			
			String tok = new String();
			String[] cons;
			String[] meds;
			List<String> med = new ArrayList<String>();
			int i = 0;
			while (i < tokens.length)
			{
				tok = tokens[i];
				cons = tok.split(",");
				meds = cons[3].split("\\+");
				Consultation consultation = new Consultation(cons[0],cons[1],cons[2],med,cons[4]);
				for (int j = 0; j < meds.length-1; j++)
				{
					consultation.getMeds().add(meds[j]);
				}
				lp.add(consultation);
				i = i + 1;
			}

		} catch (IOException e) {
			e.printStackTrace();
		}
		
		return lp;	
	}
	
	public void savePatientToFile(Patient p) throws IOException		// save to file
	{
		int n=0;
		BufferedReader in = new BufferedReader(new FileReader(patients));
		while((in.readLine())!=null)
			n++;
		in.close();
		String[] sl=new String[n];
		String str;
		int i=0;
		in = new BufferedReader(new FileReader(patients));
		while((str=in.readLine())!=null)
		{
			sl[i] = str;
			i++;
		}
		in.close(); // append
		FileWriter fw=new FileWriter(patients);
		PrintWriter out=new PrintWriter(fw);
		for (i=1; i<sl.length-1; i++)
			out.println(sl[i]);
		out.println(p.toString());
		out.close();
	}
	
	public void saveConsultationToFile(Consultation c) throws IOException		// save to file
	{
		int n=0;
		BufferedReader in = new BufferedReader(new FileReader(consultations));
		while((in.readLine())!=null)
			n++;
		in.close();
		String[] sl=new String[n];
		String str;
		int i=0;
		in = new BufferedReader(new FileReader(consultations));
		while((str=in.readLine())!=null)
		{
			sl[i] = str;
			i++;
		}
		in.close(); // append
		FileWriter fw=new FileWriter(consultations);
		PrintWriter out=new PrintWriter(fw);
		for (i=0; i<sl.length-1; i++)
			out.println(sl[i]);
		out.println(c.toString());
		out.close();
	}
}
