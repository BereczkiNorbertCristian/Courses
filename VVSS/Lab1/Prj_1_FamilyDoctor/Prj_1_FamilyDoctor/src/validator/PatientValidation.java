package validator;

import java.util.regex.Pattern;
import java.util.regex.Matcher;

import exceptions.PatientException;

public class PatientValidation {
	public static void nameValidate(String name) throws PatientException {
		if (name.length() == 0) {
			throw new PatientException("One of the required fields is empty!");
		}
		/*
		Pattern pattern = Pattern.compile("^[a-zA-Z -]+$");
		Matcher matcher = pattern.matcher(name);
		if (!matcher.find()) {
			throw new PatientException("The \"name\" field has an invalid format!");
		}
		*/
	}
	
	public static void ssnValidate(String ssn) throws PatientException {
		if (ssn.length() != 13) {
			System.out.println("ssn="+ ssn+" si lungime="+ssn.length());
			throw new PatientException("SSN has the length != 13");
		}
		Pattern pattern = Pattern.compile("^\\d+$");
		Matcher matcher = pattern.matcher(ssn);
		if (!matcher.find()) {
			throw new PatientException("The \"ssn\" field has an invalid format!");
		}
	}
	
	public static void addressValidate(String address) throws PatientException {
		if (address.length() == 0) {
			throw new PatientException("One of the required fields is empty!");
		}
	}
}
