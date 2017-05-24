//
// Created by syzegno on 28.04.17.
//


#include <stdio.h>
#include <sstream>
#include <unistd.h>
#include <fcntl.h>

#include <gtest/gtest.h>

#include "Parser.h"
#include "Attributes.h"
#include "Predicates.h"
#include "ConcreteRequirements.h"
#include "PredicatePrinter.h"
#include "UnixFileStream.h"
#include "StreamAttributeScanner.h"
#include "StreamAttributePrinter.h"
#include "StreamRequirementPrinter.h"
#include "StreamRequirementScanner.h"
#include "StreamPredicatePrinter.h"
#include "StreamPredicateScanner.h"
#include "AttributePrinter.h"

using namespace Handmada;


TEST(FilePrinterAndScanner, FilePacking)
{
    int fd = open("tmp1.txt", O_CREAT | O_TRUNC | O_RDWR, 0666);

    StringAttribute str("login", "Super Secret");
    NumberAttribute num("age", 37);
    BooleanAttribute boolean("smoking", false);
    StringAttribute veryLong("number of 360 quick-scoped enemies in this round (what round?)", "actually, it's not a numeric attribute, as you can see");
    NumberAttribute theorems("number of proven theorems", 800);

    IAttribute* attributes[] = { &str, &num, &boolean, &veryLong, &theorems };

    UnixFileStream stream(fd);
    StreamAttributePrinter packer(stream);

    for (auto attribute : attributes) {
        ASSERT_NO_THROW(attribute->accept(packer));
    }

    stream.seek(0, Whence::SET);
    StreamAttributeScanner scanner(stream);

    std::ostringstream sout;
    AttributePrinter printer(sout);

    auto iterator = std::begin(attributes);
    while (iterator != std::end(attributes)) {
        std::unique_ptr<IAttribute> attribute;
        ASSERT_NO_THROW(attribute = scanner.getNext());
        attribute->accept(printer);
        ASSERT_EQ(attribute->type(), (*iterator)->type());
        ++iterator;
    }

    const char* expected = "login: \"Super Secret\"\nage: 37\nsmoking: no\n"
            "number of 360 quick-scoped enemies in this round (what round?): \"actually, it's not a numeric attribute, as you can see\"\n"
            "number of proven theorems: 800\n";
    ASSERT_STREQ(sout.str().c_str(), expected);
    close(fd);
    unlink("tmp1.txt");
}


TEST(FilePrinterAndScanner, RequirementPrintingAndScanning)
{
    int fd = open("tmp2.txt", O_CREAT | O_TRUNC | O_RDWR, 0666);

    StringRequirement str("login");
    NumberRequirement num("age");
    BooleanRequirement boolean("has a car", "Do you have a car?");

    IRequirement* requirements[] = { &str, &num, &boolean };

    UnixFileStream stream(fd);
    StreamRequirementPrinter printer(stream);
    for (auto requirement : requirements) {
        ASSERT_NO_THROW(requirement->accept(printer));
    }

    stream.seek(0, Whence::SET);
    StreamRequirementScanner scanner(stream);
    std::unique_ptr<IRequirement> newRequirements[3];

    for (int i = 0; i < 3; i++) {
        ASSERT_NO_THROW(newRequirements[i] = scanner.getNext());
        ASSERT_STREQ(requirements[i]->name().c_str(), newRequirements[i]->name().c_str());
        ASSERT_EQ(requirements[i]->type(), newRequirements[i]->type());
    }

    BooleanRequirement* newBoolean = dynamic_cast<BooleanRequirement*>(newRequirements[2].get());
    ASSERT_NE(newBoolean, nullptr);
    ASSERT_STREQ(boolean.question().c_str(), newBoolean->question().c_str());
    close(fd);
    unlink("tmp2.txt");
}


TEST(FilePrinterAndScanner, PredicatePrintingAndScanning)
{
    int fd = open("predicates.dump", O_CREAT | O_TRUNC | O_RDWR, 0666);

    std::istringstream sin("(age >= 18 && age < 60) && drinksCoffee == yes && has_a_car == yes"
                                   "|| name == \"Nick\" && !(favouriteNumber == 3.14)"
                                   "|| drivesACar == yes || alma_mater == \"MSU\" && faculty == \"CMC\""
                                   "&& favouriteSubject == \"Happy English\"");
    Parser parser(sin);
    std::unique_ptr<Handmada::IPredicate> predicate;
    ASSERT_NO_THROW(predicate = parser.getPredicate());

    std::ostringstream original;
    PredicatePrinter printer(original);
    predicate->accept(printer);

    UnixFileStream stream(fd);
    StreamPredicatePrinter filePrinter(stream);
    ASSERT_NO_THROW(predicate->accept(filePrinter));
    stream.seek(0, Whence::SET);
    StreamPredicateScanner scanner(stream);

    std::unique_ptr<IPredicate> preCopy;
    ASSERT_NO_THROW(preCopy = scanner.getNext());

    std::ostringstream copy;
    PredicatePrinter printer1(copy);
    preCopy->accept(printer1);
    ASSERT_STREQ(original.str().c_str(), copy.str().c_str());
    unlink("predicates.dump");
}
