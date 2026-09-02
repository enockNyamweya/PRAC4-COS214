#ifndef WORKUNIT_H
#define WORKUNIT_H

#include <string>

// Forward declaration of WorkIterator to avoid circular includes
class WorkIterator;

/**
 * @brief WorkUnit: Component Base for Composite Pattern.
 * Defines uniform interface for both individual items (PackageItem) and composite groups (CargoGroup).
 */
class WorkUnit {
protected:
    std::string name;
    double baseWeight;

public:
    WorkUnit(const std::string& name, double weight = 0.0);
    virtual ~WorkUnit(); // Virtual destructor for polymorphic base classes

    std::string getName() const;
    virtual double getWeight() const;

    // Pure virtual execution method
    virtual void execute() = 0;

    // Default composite management (no-op warning for leaves)
    virtual void add(WorkUnit* unit);
    virtual void remove(WorkUnit* unit);

    // Pure virtual iterator factory method
    virtual WorkIterator* createIterator() = 0;
};

#endif // WORKUNIT_H