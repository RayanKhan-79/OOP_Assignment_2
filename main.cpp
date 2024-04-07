#include"i230745_B_Q3.h"
// Making a Change
int main()
{
		CAList tt, tt2, tt3, tt4;

		tt["OOP"] = "Dr.Ali";
		tt["OOP"] = "Mr.Shehryar";
		tt["OOP"] = "Ms.Hida";
		tt["OOP"] = "Mr.Shams";
		tt["DLD"] = "Mr.Amir";
		tt["DLD"] = "Mr.Shams";
		tt["DLD"] = "Dr.Mehwish";



		tt2["Algo"] = "Mr.Owais";
		tt2["OOP"] = "Mr.Shehryar";
		tt2["Pak Stds"] = "Mr.Ajmal";
		tt2["Pak Stds"] += "Ms.Gul";
		tt2["Pak Stds"] = "Ms.Memoona";
		tt2["Islamiat"] = "Dr.Tayab";
		tt2["Islamiat"] += "Ms.Sobia";
		tt2["Islamiat"] = "Mr.Usman";
		tt2["Islamiat"] += "Ms.Gul";
		tt2["Islamiat"] += "Mr.Anas";

		cout << "\n\ntt:\n_______________________";
		cout << tt;
		
		cout << "\n\ntt2:\n_______________________";
		cout << tt2;
	
		tt3 = tt + tt2;

		cout << "\n\ntt3 (tt + tt2):\n_______________________";
		cout << tt3;

		tt4 = tt - tt2;

		cout << "\n\ntt4 (tt - tt2):\n_______________________";
		cout << tt4;

	return 0;
}
