#include <iostream>
#include <string>

#include <zserio/ObjectArray.h>
#include <zserio/BitStreamReader.h>
#include <zserio/BitStreamWriter.h>

#include "tutorial/Employee.h"

static void printHelp()
{
    std::cout << "Usage: ZserioTutorialCpp [write_joe] [write_boss] [read]" << std::endl;
}

static void writeJoe(const std::string& employeeFile)
{
    /* declare an employee */
    tutorial::Employee joe;

    /* fill some basic type fields */
    joe.setAge(32);
    joe.setName("Joe Smith");
    joe.setSalary(5000);

    /* set an enum value, in this case the role */
    joe.setRole(tutorial::Role::DEVELOPER);

    /* declare a zserio object array which holds a zserio struct */
    zserio::ObjectArray<tutorial::Experience> skills;

    /* declare and fill the struct Experience */
    tutorial::Experience skill1;
    skill1.setYearsOfExperience(8);
    skill1.setProgrammingLanguage(tutorial::Language::CPP);
    skills.push_back(skill1);

    /* fill a second one... */
    tutorial::Experience skill2;
    skill2.setYearsOfExperience(4);
    skill2.setProgrammingLanguage(tutorial::Language::PYTHON);
    skills.push_back(skill2);

    /* assign the zserio object array to object joe */
    joe.setSkills(skills);

    /* declare a zserio BitStreamWriter */
    zserio::BitStreamWriter writer;

    /* serialize the object joe by passing the BitStreamWriter to its write() method */
    joe.write(writer);

    /* write the buffer stored in the BitStreamWriter to disk */
    writer.writeBufferToFile(employeeFile);
}

static void writeBoss(const std::string& employeeFile)
{
    /* declare an employee */
    tutorial::Employee boss;

    /* fill some basic type fields */
    boss.setAge(43);
    boss.setName("Boss");
    boss.setSalary(9000);

    /* set an enum value, in this case the role */
    boss.setRole(tutorial::Role::TEAM_LEAD);

    /* no programming skills for the boss, but a bonus! */
    boss.setBonus(10000);

    /* declare a zserio BitStreamWriter */
    zserio::BitStreamWriter writer;

    /* serialize the object boss by passing the BitStreamWriter to its write() method */
    boss.write(writer);

    /* write the buffer stored in the BitStreamWriter to disk */
    writer.writeBufferToFile(employeeFile);
}

static void readEmployee(const std::string& employeeFile)
{
    /* declare the zserio BitStreamReader and assign the file to read from */
    zserio::BitStreamReader reader(employeeFile);

    /* deserialize the stream to an Employee class */
    tutorial::Employee employee;
    employee.read(reader);

    /* data types that are always available can simply be printed out */
    std::cout << "Name: " << employee.getName() << std::endl;
    std::cout << "Age: " << static_cast<unsigned int>(employee.getAge()) << std::endl;
    std::cout << "Salary: " << employee.getSalary() << std::endl;
    std::cout << "Role: " << employee.getRole().toString() << std::endl;

    /* we have to check for optionals whether they are in the stream */
    if (employee.hasBonus())
        std::cout << "Bonus: " << employee.getBonus() << std::endl;

    /* we also have to check for conditions if they applied */
    if (employee.hasSkills())
    {
        const zserio::ObjectArray<tutorial::Experience> skills  = employee.getSkills();
        for (zserio::ObjectArray<tutorial::Experience>::const_iterator it = skills.begin();
                it != skills.end(); ++it)
        {
            const uint8_t years = it->getYearsOfExperience();
            const tutorial::Language language = it->getProgrammingLanguage();

            /* get string representation of Language enum value */
            const std::string languageString = language.toString();

            std::cout << "Skill: Language " << languageString << ", " << static_cast<unsigned int>(years) <<
                    " years" << std::endl;
        }
    }

    /* print out bit size */
    std::cout << "Bit size of employee: " << employee.bitSizeOf() << std::endl;
}

int main(int argc, char** argv)
{
    if (argc != 2)
    {
        printHelp();
        return 0;
    }

    const std::string employeeFile("employee.zsb");
    try
    {
        if (argv[1] == std::string("write_joe"))
        {
            /* writing an employee 'Joe' to file */
            writeJoe(employeeFile);
        }
        else if (argv[1] == std::string("write_boss"))
        {
            /* writing an employee 'Boss' to file */
            writeBoss(employeeFile);
        }
        else if (argv[1] == std::string("read"))
        {
            /* reading an employee from file */
            readEmployee(employeeFile);
        }
        else
        {
            printHelp();
        }
    }
    catch (const zserio::CppRuntimeException& e)
    {
        std::cout << e.what() << std::endl;
    }

    return 0;
}
