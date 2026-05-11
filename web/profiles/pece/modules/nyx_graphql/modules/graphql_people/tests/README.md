# GraphQL People Module Tests

## Overview

This directory contains automated tests for the graphql_people module, specifically testing the security fix for the CreateUser DataProducer.

## Test Coverage

### Security Fix Context

The CreateUser GraphQL endpoint previously contained a dangerous authorization bypass on line 101:
```php
// BEFORE (vulnerable):
if ($this->currentUser->hasPermission("administer users") || $this->currentUser->isAnonymous())

// AFTER (fixed):
if ($this->currentUser->hasPermission("administer users"))
```

The `isAnonymous()` check allowed anonymous users to create accounts, bypassing Drupal's normal registration controls and enabling mass account creation attacks.

### Test Types

#### 1. Kernel Tests (`src/Kernel/CreateUserTest.php`)

Tests the CreateUser DataProducer plugin directly without full Drupal bootstrap.

**Test Cases:**
- `testAnonymousUserCannotCreateAccount()` - Verifies anonymous users receive NULL response
- `testAuthenticatedUserWithoutPermissionCannotCreateAccount()` - Verifies regular users cannot create accounts
- `testAdminUserCanCreateAccount()` - Verifies admin users can still create accounts (no regression)
- `testDuplicateUserCreationHandling()` - Verifies proper exception handling for duplicate users

#### 2. Functional Tests (`src/Functional/CreateUserGraphQLTest.php`)

Tests the full GraphQL API endpoint integration with HTTP requests.

**Test Cases:**
- `testAnonymousCannotCreateUserViaGraphQL()` - Verifies anonymous GraphQL requests are rejected
- `testRegularUserCannotCreateUserViaGraphQL()` - Verifies unauthorized GraphQL requests are rejected
- `testAdminCanCreateUserViaGraphQL()` - Verifies admin GraphQL requests succeed (no regression)

## Running Tests

### Run All graphql_people Tests

```bash
# Using vendor/bin/phpunit
vendor/bin/phpunit -c web/core web/profiles/pece/modules/nyx_graphql/modules/graphql_people/tests

# Using DDEV
ddev exec vendor/bin/phpunit -c web/core web/profiles/pece/modules/nyx_graphql/modules/graphql_people/tests

# Or with Drupal's run-tests.sh
php web/core/scripts/run-tests.sh --module graphql_people
```

### Run Specific Test Classes

```bash
# Kernel tests only
vendor/bin/phpunit -c web/core web/profiles/pece/modules/nyx_graphql/modules/graphql_people/tests/src/Kernel/CreateUserTest.php

# Functional tests only
vendor/bin/phpunit -c web/core web/profiles/pece/modules/nyx_graphql/modules/graphql_people/tests/src/Functional/CreateUserGraphQLTest.php
```

### Run Specific Test Methods

```bash
# Run only the anonymous user test
vendor/bin/phpunit -c web/core --filter testAnonymousUserCannotCreateAccount web/profiles/pece/modules/nyx_graphql/modules/graphql_people/tests
```

## Expected Results

All tests should **PASS**, confirming:
1. ✅ Anonymous users **cannot** create accounts (security fix verified)
2. ✅ Regular authenticated users **cannot** create accounts (proper authorization)
3. ✅ Admin users **can** create accounts (no regression)
4. ✅ Error handling works correctly (duplicate user exceptions)

## Test Failures

If any test fails:

1. **`testAnonymousUserCannotCreateAccount` fails**: The security vulnerability still exists. Check line 101 in CreateUser.php.
2. **`testAdminUserCanCreateAccount` fails**: The security fix broke admin functionality. Review the permission check logic.
3. **Setup errors**: Ensure required modules (graphql, user, system) are available and installed.

## Maintenance

These tests should be run:
- ✅ Before deploying any changes to CreateUser.php
- ✅ As part of CI/CD pipeline
- ✅ When upgrading Drupal core or GraphQL module
- ✅ When modifying user permission logic

## Related Files

- **Implementation**: `web/profiles/pece/modules/nyx_graphql/modules/graphql_people/src/Plugin/GraphQL/DataProducer/CreateUser.php`
- **Security Fix Commit**: a51bf3399
- **QA Report**: `.auto-claude/specs/006-fix-dangerous-anonymous-user-creation-in-createuse/qa_report.md`
