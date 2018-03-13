package controller;

import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

import exceptions.ConsultationException;
import exceptions.PatientException;
import repository.Repository;
import validator.PatientValidation;
import model.Consultation;
import model.Patient;

public class DoctorController {

	private List<Patient> PatientList;
	private List<Consultation> ConsultationList;
	private Repository rep;

	/** Constructors */

	public DoctorController(Repository rep) {
		this.rep = rep;
		this.PatientList = rep.getPatientList();
		this.ConsultationList = rep.getConsultationList();
		// Get list from file in order to avoid duplicates.
	}

	/** Getters */
	public List<Patient> getPatientList() {
		return PatientList;
	}

	public List<Consultation> getConsultationList() {
		return ConsultationList;
	}

	public void setConsulationList(List<Consultation> consultationList) {
		ConsultationList = consultationList;
	}

	public int getPatientBySSN(String SSN) {
		for (int i = 0; i < PatientList.size(); i++) {
			if (PatientList.get(i).getSSN().equals(SSN))
				return i;
		}

		return -1;
	}

	public int getConsByID(String ID) {
		for (int i = 0; i < ConsultationList.size(); i++) {
			if (ConsultationList.get(i).getConsID().compareTo(ID) == 0) {
				/*
				 * System.out.println("I proud to have found " + ID + " here: "
				 * + i); System.out.println("Proof : " +
				 * ConsultationList.get(i).toString());
				 */
				return i - 1;
			}
		}

		return -1;
	}

	public Repository getRepository() {
		return rep;
	}

	/** Others */
	public void addPatient(Patient p) throws PatientException {
		if (p.getName() != null && p.getSSN() != null && p.getAddress() != null) {
			PatientValidation.nameValidate(p.getName());
			PatientValidation.ssnValidate(p.getSSN());
			PatientValidation.addressValidate(p.getAddress());
		} else {
			throw new PatientException("Null fields");
		}
		PatientList.add(p);
		try {
			rep.savePatientToFile(p);
		} catch (IOException e) {
			e.printStackTrace();
		}
	}

	// adding of a new consultation for a patient (consultation date,
	// diagnostic, prescription drugs)

	public void addConsultation(String consID, String patientSSN, String diag,
			List<String> meds, String date) throws ConsultationException {
		if (meds == null)
			throw new ConsultationException("meds is null");

		if (consID != null && patientSSN != null
				&& diag != null && meds.size() != 0
				&& this.getPatientBySSN(patientSSN) > -1
				&& this.getConsByID(consID) == -1) {
			Consultation c = new Consultation(consID, patientSSN, diag, meds, date);
			ConsultationList.add(c);
			try {
				rep.saveConsultationToFile(c);
			} catch (IOException e) {
				e.printStackTrace();
			}

			Patient p = new Patient();
			p = this.getPatientList().get(
					this.getPatientBySSN(c.getPatientSSN()));
			p.setConsNum(p.getConsNum() + 1);
		}
		else {
			throw new ConsultationException("invalid arguments");
		}

	}

	public List<Patient> getPatientsWithDisease(String disease) throws PatientException {
		List<Consultation> c = this.getConsultationList();
		List<Patient> p = new ArrayList<Patient>();
		if (disease != null) {
			if (disease.length() == 0) {
				throw new PatientException("Empty disease provided");
			}
			int chk = 1;

			for (int i = 0; i < c.size(); i++) {
				if (c.get(i).getDiag().toLowerCase()
						.contains(disease.toLowerCase())) // so that it is case
															// insensitive
				{
					for (int j = 0; j < p.size(); j++) // verify patient was
															// not already added
					{
						if (p.get(j).getSSN().equals(c.get(i).getPatientSSN())) {
							chk = p.get(j).getConsNum();
						}
					}

					if (chk == 1) {
						p.add(this.getPatientList().get(
								this.getPatientBySSN(c.get(i).getPatientSSN()))); // get
																					// Patient
																					// by
																					// SSN
					}
					chk = 1;
				}
			}

			// Sort the list

			Patient paux = new Patient();

			for (int i = 0; i < p.size(); i++)
				for (int j = i + 1; j < p.size() - 1; j++)
					if (p.get(j - 1).getConsNum() < p.get(j).getConsNum()) {
						paux = p.get(j - 1);
						p.set(j - 1, p.get(j));
						p.set(j, paux);
					}
		}
		else {
			throw new PatientException("Null disease parameter provided");
		}
		return p;
	}

	/*
	 * For debugging purposes public void printList() { for (int i = 0; i <
	 * PatientList.size(); i++) {
	 * System.out.println(PatientList.get(i).toString()); } }
	 */

}
