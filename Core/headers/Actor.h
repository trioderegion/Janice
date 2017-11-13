#pragma once

class AActor
{
public:
	/** default initalization */
	AActor::AActor() = default;
	
	/** Initialize with a name */
	explicit AActor::AActor(const std::string& name) : Name{ name } {};

	virtual AActor::~AActor() {};

	// ACCESSORS

	/* returns actor name */
	const std::string& GetName() const { return Name; };

private:
	std::string Name;
};