# Hospital Management System

A C++ console application for managing hospital patient records.

## Features

- **Add Patient** - Register new patients with ID, name, DOB, gender, clinic, and medications
- **Delete Patient** - Remove patient records by ID
- **Update Patient** - Modify existing patient information
- **View All Records** - Display all registered patients
- **Search by ID** - Find a specific patient using their 10-digit ID
- **Sort Records** - Sort patients by ID (descending order)
- **Filter by Gender** - View patients filtered by gender (M/F)
- **Filter by Clinic** - View patients from a specific clinic
- **Save Data** - Persist records to file (append or overwrite modes)

## Clinics Supported

- Dental
- Respiratory
- Family Medicine
- Vaccine
- Custom clinics

## Data Storage

Patient records are saved to `Records.txt` using a delimiter-based format. The system also maintains a `Log.text` file to track application usage.

## Building

```bash
g++ -g Hospital_System.cpp -o Hospital_System.exe
```

## Usage

Run the executable and follow the menu prompts:

```
1  - Add a person
2  - Delete a person
3  - Update a person
4  - View all records
5  - Find the person by ID
6  - Sort records by max ID
7  - Show person by gender
8  - Show person by Clinic
9  - Save Hospital Data (append to existing)
10 - Save Hospital Data (overwrite)
-1 - Exit
```

## Patient Data Structure

Each patient record includes:
- **ID**: 10-digit unique identifier
- **Name**: Full name
- **Date of Birth**: Day/Month/Year
- **Gender**: M or F
- **Clinic**: Assigned clinic
- **Medications**: Up to 2 medications with dose and frequency

## Requirements

- C++ compiler (g++ recommended)
- Windows/Linux/macOS
