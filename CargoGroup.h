#ifndef CARGOGROUP_H
#define CARGOGROUP_H

#include "WorkUnit.h"
#include <vector>

/**
 * @brief CargoGroup: Composite class managing child WorkUnit pointers.
 * Represents Warehouses, Distribution Hubs, and Shipping Containers (3+ nesting levels).
 */
class CargoGroup : public WorkUnit {
private:
    std::vector<WorkUnit*> children;

public:
    CargoGroup(const std::string& name);
    virtual ~CargoGroup(); // Deletes all children in vector to prevent memory leaks

    void execute() override;
    double getWeight() const override;

    void add(WorkUnit* unit) override;
    void remove(WorkUnit* unit) override;

    const std::vector<WorkUnit*>& getChildren() const;
    WorkIterator* createIterator() override;
};

#endif // CARGOGROUP_H