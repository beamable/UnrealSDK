#include "BeamUserSlots.spec.h"

#include "Engine/Engine.h"
#include "Misc/AutomationTest.h"

#include "BeamBackend/BeamBackend.h"
#include "BeamUserSlotsTestCallbacks.h"
#include "JsonObjectConverter.h"

void FBeamUserSlotsSpec::Define()
{
	Describe("Manipulating User Slots Data", [=, this]()
	{
		const FUserSlot TestSlot{"Automated_Test_Slot"};

		const FString FakeAccessToken{"ACCESS_TOKEN"}, FakeRefreshToken{"REFRESH_TOKEN"};
		const FBeamCid FakeCid = GetDefault<UBeamCoreSettings>()->TargetRealm.Cid;
		const FBeamPid FakePid = GetDefault<UBeamCoreSettings>()->TargetRealm.Pid;
		
		const int64 &FakeExpiresIn{1234}, FakeGamerTag{0000001};

		BeforeEach([=, this]()
		{
			BeamUserSlots = GEngine->GetEngineSubsystem<UBeamUserSlots>();

			// Prepare UserSlot Tests with Blueprint-compatible mock handler
			Callbacks = NewObject<UBeamUserSlotsTestCallbacks>();
			Callbacks->BeamUserSlots = BeamUserSlots;
			Callbacks->Spec = this;
		});

		AfterEach([=, this]()
		{
			// We clean up the registered UObject functions for the test
			for (const auto& AddedUObjectTestHandler : AddedUObjectTestHandlers)
				BeamUserSlots->GlobalUserSlotClearedHandler.Remove(Callbacks, AddedUObjectTestHandler);
			AddedUObjectTestHandlers.Reset();

			// We clean up the delegates we have registered for the test (mostly lambdas).
			for (const auto& AddedTestHandler : AddedTestHandlers)
				BeamUserSlots->GlobalUserSlotClearedCodeHandler.Remove(AddedTestHandler);
			AddedTestHandlers.Reset();

			// We clear the Automated Test Slot
			BeamUserSlots->ClearUserAtSlot(TestSlot, USCR_Manual, true);

			// Delete the file for the test slot
			IFileManager& FileManager = IFileManager::Get();
			FileManager.Delete(*BeamUserSlots->GetSavedSlotAuthFilePath(UBeamUserSlots::GetNamespacedSlotId(TestSlot, nullptr)));
			FileManager.Delete(*BeamUserSlots->GetSavedSlotAccountFilePath(UBeamUserSlots::GetNamespacedSlotId(TestSlot, nullptr)));
		});


		It("should set and get the user data at the Test Slot", [=, this]()
		{
			BeamUserSlots->SetAuthenticationDataAtSlot(TestSlot, FakeAccessToken, FakeRefreshToken, FDateTime::UtcNow().ToUnixTimestamp(), FakeExpiresIn, FakeCid, FakePid, nullptr);
			FBeamRealmUser RealmUser;
			auto bFound = BeamUserSlots->GetUserDataAtSlot(TestSlot, RealmUser, nullptr);

			TestTrue("successfully added user to slot", bFound);
			TestTrue("added correct user data to slot", RealmUser.AuthToken.AccessToken == FakeAccessToken);
			TestTrue("added correct user data to slot", RealmUser.AuthToken.RefreshToken == FakeRefreshToken);
			TestTrue("added correct user data to slot", RealmUser.AuthToken.ExpiresIn == FakeExpiresIn);

			TestTrue("added correct user data to slot", RealmUser.RealmHandle.Cid == FakeCid);
			TestTrue("added correct user data to slot", RealmUser.RealmHandle.Pid == FakePid);

			const auto ReplacementAccessToken = TEXT("OVERRIDEN_ACCESS_TOKEN");
			BeamUserSlots->SetAuthenticationDataAtSlot(TestSlot, ReplacementAccessToken, FakeRefreshToken, FDateTime::UtcNow().ToUnixTimestamp(), FakeExpiresIn, FakeCid, FakePid, nullptr);
			bFound = BeamUserSlots->GetUserDataAtSlot(TestSlot, RealmUser, nullptr);

			TestTrue("successfully overwritten user data into slot", bFound);
			TestTrue("added correct user data to slot", RealmUser.AuthToken.AccessToken == ReplacementAccessToken);
			TestTrue("added correct user data to slot", RealmUser.AuthToken.RefreshToken == FakeRefreshToken);
			TestTrue("added correct user data to slot", RealmUser.AuthToken.ExpiresIn == FakeExpiresIn);

			TestTrue("added correct user data to slot", RealmUser.RealmHandle.Cid == FakeCid);
			TestTrue("added correct user data to slot", RealmUser.RealmHandle.Pid == FakePid);
		});

		It("should find the user slot with the given refresh token and pid", [=, this]()
		{
			BeamUserSlots->SetAuthenticationDataAtSlot(TestSlot, FakeAccessToken, FakeRefreshToken, FDateTime::UtcNow().ToUnixTimestamp(), FakeExpiresIn, FakeCid, FakePid, nullptr);

			FBeamRealmUser RealmUser;
			FUserSlot UserSlot;
			FString NamespacedSlotId;
			auto bFound = BeamUserSlots->GetUserDataWithRefreshTokenAndPid(FakeRefreshToken, FakePid, RealmUser, UserSlot, NamespacedSlotId);

			TestTrue("found user based on refresh token and pid", bFound);
			TestTrue("user was in expected slot", UserSlot.Name == TestSlot.Name);
			TestTrue("found correct user based on refresh token and pid", RealmUser.AuthToken.AccessToken == FakeAccessToken);
			TestTrue("found correct user based on refresh token and pid", RealmUser.AuthToken.RefreshToken == FakeRefreshToken);
			TestTrue("found correct user based on refresh token and pid", RealmUser.AuthToken.ExpiresIn == FakeExpiresIn);

			TestTrue("found correct user based on refresh token and pid", RealmUser.RealmHandle.Cid == FakeCid);
			TestTrue("found correct user based on refresh token and pid", RealmUser.RealmHandle.Pid == FakePid);

			const auto ReplacementRefreshToken = TEXT("OVERRIDEN_REFRESH_TOKEN");
			BeamUserSlots->SetAuthenticationDataAtSlot(TestSlot, FakeAccessToken, ReplacementRefreshToken, FDateTime::UtcNow().ToUnixTimestamp(), FakeExpiresIn, FakeCid, FakePid, nullptr);
			bFound = BeamUserSlots->GetUserDataWithRefreshTokenAndPid(ReplacementRefreshToken, FakePid, RealmUser, UserSlot, NamespacedSlotId);

			TestTrue("successfully overwritten user data into slot", bFound);
			TestTrue("user was in expected slot", UserSlot.Name == TestSlot.Name);
			TestTrue("found correct user based on refresh token and pid", RealmUser.AuthToken.AccessToken == FakeAccessToken);
			TestTrue("found correct user based on refresh token and pid", RealmUser.AuthToken.RefreshToken == ReplacementRefreshToken);
			TestTrue("found correct user based on refresh token and pid", RealmUser.AuthToken.ExpiresIn == FakeExpiresIn);
			TestTrue("found correct user based on refresh token and pid", RealmUser.RealmHandle.Cid == FakeCid);
			TestTrue("found correct user based on refresh token and pid", RealmUser.RealmHandle.Pid == FakePid);
		});

		It("should set the user slot AND save its file to disk then reload the saved user at that slot", [=, this]()
		{
			BeamUserSlots->SetAuthenticationDataAtSlot(TestSlot, FakeAccessToken, FakeRefreshToken, FDateTime::UtcNow().ToUnixTimestamp(), FakeExpiresIn, FakeCid, FakePid, nullptr);
			BeamUserSlots->SetGamerTagAtSlot(TestSlot, FakeGamerTag, nullptr);
			BeamUserSlots->TriggerUserAuthenticatedIntoSlot(TestSlot, {}, nullptr);
			BeamUserSlots->SaveSlot(TestSlot, nullptr);

			FBeamRealmUser RealmUser;
			auto bFound = BeamUserSlots->GetUserDataAtSlot(TestSlot, RealmUser, nullptr);
			TestTrue("found user", bFound);

			IFileManager& FileManager = IFileManager::Get();
			FileManager.FileExists(*BeamUserSlots->GetSavedSlotAuthFilePath(UBeamUserSlots::GetNamespacedSlotId(TestSlot, nullptr)));

			// Clear the slot so we can verify the loading function actually works
			BeamUserSlots->SetAuthenticationDataAtSlot(TestSlot, TEXT(""), TEXT(""), FDateTime::UtcNow().ToUnixTimestamp(), 0,FBeamCid(TEXT("")), FBeamPid(TEXT("")), nullptr);
			BeamUserSlots->SetGamerTagAtSlot(TestSlot, -1, nullptr);

			// Load the user from the serialized file and see if it was loaded correctly.
			const auto bLoaded = BeamUserSlots->TryLoadSavedUserAtSlotAndAuth(TestSlot, nullptr);
			bFound             = BeamUserSlots->GetUserDataAtSlot(TestSlot, RealmUser, nullptr);

			TestTrue("successfully added user to slot", bFound);
			TestTrue("successfully added user to slot from serialized user file", bLoaded == UBeamUserSlots::LoadSavedUserResult_Success);
			TestTrue("added correct user data to slot", RealmUser.GamerTag == FakeGamerTag);
			TestTrue("added correct user data to slot", RealmUser.AuthToken.AccessToken == FakeAccessToken);
			TestTrue("added correct user data to slot", RealmUser.AuthToken.RefreshToken == FakeRefreshToken);
			TestTrue("added correct user data to slot", RealmUser.AuthToken.ExpiresIn == FakeExpiresIn);

			TestTrue("added correct user data to slot", RealmUser.RealmHandle.Cid == FakeCid);
			TestTrue("added correct user data to slot", RealmUser.RealmHandle.Pid == FakePid);
		});

		It("should fail gracefully when trying to load an unsaved UserSlot", [=, this]()
		{
			// Tries to load the user from a non-existing Saved UserSlot and sees if it gracefully returns false.
			const auto bLoaded = BeamUserSlots->TryLoadSavedUserAtSlotAndAuth(TestSlot, nullptr);
			TestTrue("failed to add user to slot since no saved user existed at that slot", !bLoaded);
		});

		It("should save a user and then clear them BUT don't clear the saved user", [=, this]()
		{
			BeamUserSlots->SetAuthenticationDataAtSlot(TestSlot, FakeAccessToken, FakeRefreshToken, FDateTime::UtcNow().ToUnixTimestamp(), FakeExpiresIn, FakeCid, FakePid, nullptr);
			BeamUserSlots->SetGamerTagAtSlot(TestSlot, FakeGamerTag, nullptr);
			BeamUserSlots->TriggerUserAuthenticatedIntoSlot(TestSlot, {}, nullptr);
			BeamUserSlots->SaveSlot(TestSlot, nullptr);

			FBeamRealmUser RealmUser;
			const auto bFound = BeamUserSlots->GetUserDataAtSlot(TestSlot, RealmUser, nullptr);
			TestTrue("found user", bFound);

			const auto Handle = BeamUserSlots->GlobalUserSlotClearedCodeHandler.AddLambda([=, this]
			(const EUserSlotClearedReason& UserSlotClearedReason, const FUserSlot& UserSlot, const FBeamRealmUser& BeamRealmUser, const UObject* Context)
				{
					FBeamRealmUser RealmUserAfterClear;
					const auto bFoundAfterClear = BeamUserSlots->GetUserDataAtSlot(TestSlot, RealmUserAfterClear, Context);
					TestTrue("failed to find user after clear", !bFoundAfterClear);

					// Test the clear parameters are forwarded correctly 
					TestTrue("Reason is what expected", UserSlotClearedReason == USCR_Manual);
					TestTrue("UserSlot is the cleared one", UserSlot == TestSlot);

					// Test that, even though we cleared the user, we still have access to the data at the moment of clearing
					TestTrue("Realm User has the correct data of the moment of clearing", BeamRealmUser.GamerTag.AsLong == FakeGamerTag);
					TestTrue("Realm User has the correct data of the moment of clearing", BeamRealmUser.AuthToken.AccessToken == FakeAccessToken);
					TestTrue("Realm User has the correct data of the moment of clearing", BeamRealmUser.AuthToken.RefreshToken == FakeRefreshToken);
					TestTrue("Realm User has the correct data of the moment of clearing", BeamRealmUser.AuthToken.ExpiresIn == FakeExpiresIn);
					TestTrue("Realm User has the correct data of the moment of clearing", BeamRealmUser.RealmHandle.Cid == FakeCid);
					TestTrue("Realm User has the correct data of the moment of clearing", BeamRealmUser.RealmHandle.Pid == FakePid);
				});

			AddedTestHandlers.Add(Handle);

			// Clear the slot so we can verify the loading function actually works
			BeamUserSlots->ClearUserAtSlot(TestSlot, USCR_Manual, false);

			// Load the user from the serialized file and see if it was loaded correctly.
			FBeamRealmUser RealmUserAfterReload;
			const auto     bLoaded           = BeamUserSlots->TryLoadSavedUserAtSlotAndAuth(TestSlot, nullptr);
			const auto     bFoundAfterReload = BeamUserSlots->GetUserDataAtSlot(TestSlot, RealmUserAfterReload, nullptr);

			// Test that the serialized file was not cleared.
			TestTrue("successfully added user to slot", bFoundAfterReload);
			TestTrue("successfully added user to slot from serialized user file", bLoaded == UBeamUserSlots::LoadSavedUserResult_Success);
			TestTrue("added correct user data to slot", RealmUser.AuthToken.AccessToken == FakeAccessToken);
			TestTrue("added correct user data to slot", RealmUser.AuthToken.RefreshToken == FakeRefreshToken);
			TestTrue("added correct user data to slot", RealmUser.AuthToken.ExpiresIn == FakeExpiresIn);

			TestTrue("added correct user data to slot", RealmUser.RealmHandle.Cid == FakeCid);
			TestTrue("added correct user data to slot", RealmUser.RealmHandle.Pid == FakePid);
		});

		It("should save a user and then clear them AND clear the saved used", [=, this]()
		{
			BeamUserSlots->SetAuthenticationDataAtSlot(TestSlot, FakeAccessToken, FakeRefreshToken, FDateTime::UtcNow().ToUnixTimestamp(), FakeExpiresIn, FakeCid, FakePid, nullptr);
			BeamUserSlots->SetGamerTagAtSlot(TestSlot, FakeGamerTag, nullptr);
			BeamUserSlots->TriggerUserAuthenticatedIntoSlot(TestSlot, {}, nullptr);
			BeamUserSlots->SaveSlot(TestSlot, nullptr);

			FBeamRealmUser RealmUser;
			const auto bFound = BeamUserSlots->GetUserDataAtSlot(TestSlot, RealmUser, nullptr);
			TestTrue("found user", bFound);

			const auto Handle = BeamUserSlots->GlobalUserSlotClearedCodeHandler.AddLambda([=, this]
			(const EUserSlotClearedReason& UserSlotClearedReason, const FUserSlot& UserSlot, const FBeamRealmUser& BeamRealmUser, const UObject* Context)
				{
					FBeamRealmUser RealmUserAfterClear;
					const auto bFoundAfterClear = BeamUserSlots->GetUserDataAtSlot(TestSlot, RealmUserAfterClear, Context);
					TestTrue("failed to find user after clear", !bFoundAfterClear);

					// Test the clear parameters are forwarded correctly 
					TestTrue("Reason is what expected", UserSlotClearedReason == USCR_Manual);
					TestTrue("UserSlot is the cleared one", UserSlot == TestSlot);

					// Test that, even though we cleared the user, we still have access to the data at the moment of clearing
					TestTrue("Realm User has the correct data of the moment of clearing", BeamRealmUser.GamerTag == FakeGamerTag);
					TestTrue("Realm User has the correct data of the moment of clearing", BeamRealmUser.AuthToken.AccessToken == FakeAccessToken);
					TestTrue("Realm User has the correct data of the moment of clearing", BeamRealmUser.AuthToken.RefreshToken == FakeRefreshToken);
					TestTrue("Realm User has the correct data of the moment of clearing", BeamRealmUser.AuthToken.ExpiresIn == FakeExpiresIn);
					TestTrue("Realm User has the correct data of the moment of clearing", BeamRealmUser.RealmHandle.Cid == FakeCid);
					TestTrue("Realm User has the correct data of the moment of clearing", BeamRealmUser.RealmHandle.Pid == FakePid);
				});
			AddedTestHandlers.Add(Handle);

			// Clear the slot so we can verify the loading function actually works
			BeamUserSlots->ClearUserAtSlot(TestSlot, USCR_Manual, true);

			// Load the user from the serialized file and see if it was loaded correctly.
			FBeamRealmUser RealmUserAfterReload;
			const auto bLoaded = BeamUserSlots->TryLoadSavedUserAtSlotAndAuth(TestSlot, nullptr);

			// Test that the serialized file was cleared.					
			TestTrue("successfully added user to slot from serialized user file", !bLoaded);
		});
	});
}
