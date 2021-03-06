// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "chrome/browser/chromeos/login/user_manager.h"

#include "base/command_line.h"
#include "base/prefs/pref_registry_simple.h"
#include "chrome/browser/browser_process.h"
#include "chrome/browser/browser_process_platform_part_chromeos.h"
#include "chrome/browser/chromeos/login/user_manager_impl.h"
#include "chrome/browser/chromeos/profiles/profile_helper.h"
#include "chrome/common/chrome_switches.h"

namespace chromeos {

// static
const char UserManager::kStubUser[] = "stub-user@example.com";

// static
const char UserManager::kSignInUser[] = "sign-in-user-id";

// static
// Should match cros constant in platform/libchromeos/chromeos/cryptohome.h
const char UserManager::kGuestUserName[] = "$guest";

// static
const char UserManager::kLocallyManagedUserDomain[] =
    "locally-managed.localhost";


// static
const char UserManager::kRetailModeUserName[] = "demouser@";
static UserManager* g_user_manager = NULL;

UserManager::Observer::~Observer() {
}

void UserManager::Observer::LocalStateChanged(UserManager* user_manager) {
}

void UserManager::UserSessionStateObserver::ActiveUserChanged(
    const User* active_user) {
}

void UserManager::UserSessionStateObserver::UserAddedToSession(
    const User* active_user) {
}

void UserManager::UserSessionStateObserver::ActiveUserHashChanged(
    const std::string& hash) {
}

void UserManager::UserSessionStateObserver::
PendingUserSessionsRestoreFinished() {
}

UserManager::UserSessionStateObserver::~UserSessionStateObserver() {
}

UserManager::UserAccountData::UserAccountData(const base::string16& display_name,
                                              const base::string16& given_name,
                                              const std::string& locale)
    : display_name_(display_name),
      given_name_(given_name),
      locale_(locale) {
}

UserManager::UserAccountData::~UserAccountData() {}

// static
void UserManager::Initialize() {
  CHECK(!g_user_manager);
  g_user_manager = new UserManagerImpl();
}

// static
bool UserManager::IsInitialized() {
  return g_user_manager;
}

void UserManager::Destroy() {
  DCHECK(g_user_manager);
  delete g_user_manager;
  g_user_manager = NULL;
}

// static
UserManager* UserManager::Get() {
  CHECK(g_user_manager);
  return g_user_manager;
}

// static
bool UserManager::IsMultipleProfilesAllowed() {
  return CommandLine::ForCurrentProcess()->HasSwitch(
      ::switches::kMultiProfiles);
}

UserManager::~UserManager() {
}

// static
UserManager* UserManager::SetForTesting(UserManager* user_manager) {
  UserManager* previous_user_manager = g_user_manager;
  g_user_manager = user_manager;
  return previous_user_manager;
}

ScopedUserManagerEnabler::ScopedUserManagerEnabler(UserManager* user_manager)
    : previous_user_manager_(UserManager::SetForTesting(user_manager)) {
}

ScopedUserManagerEnabler::~ScopedUserManagerEnabler() {
  UserManager::Get()->Shutdown();
  UserManager::Destroy();
  UserManager::SetForTesting(previous_user_manager_);
}

ScopedTestUserManager::ScopedTestUserManager() {
  UserManager::Initialize();

  // ProfileHelper has to be initialized after UserManager instance is created.
  g_browser_process->platform_part()->profile_helper()->Initialize();
}

ScopedTestUserManager::~ScopedTestUserManager() {
  UserManager::Get()->Shutdown();
  UserManager::Destroy();
}

}  // namespace chromeos
