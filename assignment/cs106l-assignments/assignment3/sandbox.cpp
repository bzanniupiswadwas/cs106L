/*
 * CS106L Assignment 3: Make a Class
 * Created by Fabio Ibanez with modifications by Jacob Roberts-Baca.
 */

 #include "class.h"
 #include <iostream>
void sandbox() {
  Cser cser1;
  Cser cser2("Daivi", "python", 18);
  std::cout << cser1.getname() << std::endl;
  std::cout << cser2.getname() << std::endl;
  std::cout << cser1.getjob() << std::endl;
}

