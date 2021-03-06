#pragma once

#include "Sandbox.h"

struct LuaSandbox
{
    LuaSandbox(sol::state_view aStateView);
    ~LuaSandbox() = default;

    void Initialize(sol::state_view aStateView);
    void ResetState();

    size_t CreateSandbox(const std::filesystem::path& acPath, bool aEnableExtraLibs = true, bool aEnableDB = true, bool aEnableIO = true);

    std::shared_ptr<spdlog::logger> InitializeLoggerForSandbox(Sandbox& aSandbox, const std::string& acName) const;
    
    sol::protected_function_result ExecuteFile(const std::string& acPath);
    sol::protected_function_result ExecuteString(const std::string& acString);
    
    Sandbox& operator[](size_t aID);
    const Sandbox& operator[](size_t aID) const;
    
private:

    void InitializeExtraLibsForSandbox(Sandbox& aSandbox) const;
    void InitializeDBForSandbox(Sandbox& aSandbox) const;
    void InitializeIOForSandbox(Sandbox& aSandbox); 
    
    sol::state_view m_lua;
    sol::environment m_env{ };
    std::vector<Sandbox> m_sandboxes{ };
    TiltedPhoques::Map<std::string, sol::object> m_modules{ };
};