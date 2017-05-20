//
// Created by syzegno on 28.04.17.
//

#ifndef EQUEUE_V2_IATTRIBUTE_H
#define EQUEUE_V2_IATTRIBUTE_H


#include <string>
#include <memory>

#include "AttributeType.h"


namespace Handmada {
    class IAttributeVisitor;


    /**
     * This interface represents user's attributes, i.e. "age", "login" and many other.
     * Currently, the system supports only three IAttribute implementations:
     * <ul>
     *  <li>StringAttribute (underlying type: std::string)</li>
     *  <li>NumberAttribute (double)</li>
     *  <li>BooleanAttribute (bool)</li>
     * </ul>
     */
    class IAttribute
    {
    public:
        virtual const std::string& name() const = 0;
        virtual AttributeType::Type type() const = 0;
        /**
         * Each attribute has to implement compareTo() method since ComparisonPredicate
         * relies on it.
         * The author realizes that such an approach limits the range of possible
         * comparison algorithms. For instance, it is not possible to implement
         * "loose equality" comparison for StringAttribute (inspired by JavaScript).
         * This method is used because it simplifies the logic
         * of the rest of the program.
         * Feel free to make any changes to this part of the project if you have
         * a better solution
         * @param attribute attribute that will be compared to
         * @return positive number if "this" attribute is "greater",
         * negative if it is "less" and zero if it is equal to "attribute"
         */
        virtual int compareTo(const IAttribute& attribute) const = 0;
        virtual void accept(IAttributeVisitor& visitor) const = 0;
        virtual std::unique_ptr<IAttribute> clone() const = 0;

        virtual ~IAttribute() { }
    };
}

#endif //EQUEUE_V2_IATTRIBUTE_H
