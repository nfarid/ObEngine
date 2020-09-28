#include <Event/EventNamespace.hpp>
#include <Event/Exceptions.hpp>

namespace obe::Event
{
    EventNamespace::EventNamespace(const std::string& name)
        : m_name(name)
    {
    }

    EventGroupPtr EventNamespace::createGroup(const std::string& group)
    {
        Debug::Log->debug(
            "<EventNamespace> Creating EventGroup '{}' in Namespace '{}'", group, m_name);
        if (!m_groups.count(group))
        {
            EventGroupPtr newGroup(new EventGroup(m_name, group),
                [this](EventGroup* ptr) { this->removeGroup(ptr); });
            m_groups.emplace(group, newGroup);
            return newGroup;
        }
        throw Exceptions::EventGroupAlreadyExists(m_name, group, EXC_INFO);
    }

    EventGroupPtr EventNamespace::joinGroup(const std::string& group)
    {
        Debug::Log->debug(
            "<EventNamespace> Joining EventGroup '{}' in Namespace '{}'", group, m_name);
        if (auto groupPtr = m_groups.find(group); groupPtr != m_groups.end())
        {
            if (groupPtr->second.lock()->isJoinable())
            {
                return EventGroupPtr(groupPtr->second.lock());
            }
            throw Exceptions::EventGroupNotJoinable(m_name, group, EXC_INFO);
        }

        throw Exceptions::UnknownEventGroup(
            m_name, group, this->getAllGroupsNames(), EXC_INFO);
    }

    std::vector<std::string> EventNamespace::getAllGroupsNames() const
    {
        std::vector<std::string> allNames;
        allNames.reserve(m_groups.size());
        std::transform(m_groups.begin(), m_groups.end(), allNames.begin(),
            [](const auto& pair) { return pair.first; });
        return allNames;
    }

    void EventNamespace::removeGroup(EventGroup* group)
    {
        Debug::Log->debug("<EventNamespace> Removing EventGroup '{}' from Namespace '{}'",
            group->getName(), m_name);
        m_groups.erase(group->getName());
    }

    bool EventNamespace::doesGroupExists(const std::string& group) const
    {
        return m_groups.count(group);
    }
}