/* Author: DJfromSpace (Dillon E Jones) */
#pragma once
#include <cstdint>
#include <string>

// GameObject is the smallest editor-facing and runtime-facing object unit in the engine.
// It exists to give the project a stable object concept before the full component model
// and ECS-backed runtime are implemented.
//
// Minimal Day 5 scope:
// - stable object identity
// - human-readable object name
// - active state that both runtime and editor can respect
//
// Explicitly not in scope yet:
// - parent/child hierarchy
// - transform data
// - component storage
// - serialization logic
// - gameplay behavior
class GameObject
{
public:
	using Id = std::uint32_t;

	GameObject();
	GameObject(Id objectId, std::string objectName, bool isActive = true);
	~GameObject();

	Id GetId() const;
	const std::string& GetName() const;
	bool IsActive() const;

	void SetName(const std::string& objectName);
	void SetActive(bool isActive);

private:
	Id id;
	std::string name;
	bool active;
};
