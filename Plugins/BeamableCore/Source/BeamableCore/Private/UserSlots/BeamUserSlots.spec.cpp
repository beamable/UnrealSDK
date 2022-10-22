#include "BeamUserSlots.spec.h"

#include "Engine/Engine.h"
#include "Misc/AutomationTest.h"

#include "BeamBackend/BeamBackend.h"
#include "BeamUserSlotsTestCallbacks.h"
#include "JsonObjectConverter.h"

void FBeamUserSlotsSpec::Define()
{
	Describe("Manipulating User Slots Data", [this]()
	{
		const FUserSlot TestSlot{"Automated_Test_Slot"};	

		const FString FakeAccessToken{"ACCESS_TOKEN"}, FakeRefreshToken{"REFRESH_TOKEN"}, FakeCid{"FAKE_CID"}, FakePid{"FAKE_PID"};
		const int64& FakeExpiresIn{1234};

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
			
			// We clean up the delegates we have registered for the test (mostly lamdas).
			for (const auto& AddedTestHandler : AddedTestHandlers)
				BeamUserSlots->GlobalUserSlotClearedCodeHandler.Remove(AddedTestHandler);
			AddedTestHandlers.Reset();

			// We clear the Automated Test Slot
			BeamUserSlots->ClearUserAtSlot(TestSlot, Manual, true);

			// Delete the file for the test slot
			IFileManager& FileManager = IFileManager::Get();
			FileManager.Delete(*BeamUserSlots->GetSavedSlotPath(TestSlot));
		});


		It("should set and get the user data at the Test Slot", [=, this]()
		{
			BeamUserSlots->SetUserAtSlot(TestSlot, FakeAccessToken, FakeRefreshToken, FakeExpiresIn, FakeCid, FakePid);
			FBeamRealmUser RealmUser;
			auto bFound = BeamUserSlots->GetUserDataAtSlot(TestSlot, RealmUser);

			TestTrue("successfully added user to slot", bFound);
			TestTrue("added correct user data to slot", RealmUser.AuthToken.AccessToken == FakeAccessToken);
			TestTrue("added correct user data to slot", RealmUser.AuthToken.RefreshToken == FakeRefreshToken);
			TestTrue("added correct user data to slot", RealmUser.AuthToken.ExpiresIn == FakeExpiresIn);

			TestTrue("added correct user data to slot", RealmUser.RealmHandle.Cid == FakeCid);
			TestTrue("added correct user data to slot", RealmUser.RealmHandle.Pid == FakePid);

			const auto ReplacementAccessToken = TEXT("OVERRIDEN_ACCESS_TOKEN");
			BeamUserSlots->SetUserAtSlot(TestSlot, ReplacementAccessToken, FakeRefreshToken, FakeExpiresIn, FakeCid, FakePid);
			bFound = BeamUserSlots->GetUserDataAtSlot(TestSlot, RealmUser);

			TestTrue("successfully overwritten user data into slot", bFound);
			TestTrue("added correct user data to slot", RealmUser.AuthToken.AccessToken == ReplacementAccessToken);
			TestTrue("added correct user data to slot", RealmUser.AuthToken.RefreshToken == FakeRefreshToken);
			TestTrue("added correct user data to slot", RealmUser.AuthToken.ExpiresIn == FakeExpiresIn);

			TestTrue("added correct user data to slot", RealmUser.RealmHandle.Cid == FakeCid);
			TestTrue("added correct user data to slot", RealmUser.RealmHandle.Pid == FakePid);
		});

		It("should find the user slot with the given refresh token and pid", [=, this]()
		{
			BeamUserSlots->SetUserAtSlot(TestSlot, FakeAccessToken, FakeRefreshToken, FakeExpiresIn, FakeCid, FakePid);

			FBeamRealmUser RealmUser;
			FUserSlot UserSlot;
			auto bFound = BeamUserSlots->GetUserDataWithRefreshTokenAndPid(FakeRefreshToken, FakePid, RealmUser, UserSlot);

			TestTrue("found user based on refresh token and pid", bFound);
			TestTrue("user was in expected slot", UserSlot.Name == TestSlot.Name);
			TestTrue("found correct user based on refresh token and pid", RealmUser.AuthToken.AccessToken == FakeAccessToken);
			TestTrue("found correct user based on refresh token and pid", RealmUser.AuthToken.RefreshToken == FakeRefreshToken);
			TestTrue("found correct user based on refresh token and pid", RealmUser.AuthToken.ExpiresIn == FakeExpiresIn);

			TestTrue("found correct user based on refresh token and pid", RealmUser.RealmHandle.Cid == FakeCid);
			TestTrue("found correct user based on refresh token and pid", RealmUser.RealmHandle.Pid == FakePid);

			const auto ReplacementRefreshToken = TEXT("OVERRIDEN_REFRESH_TOKEN");
			BeamUserSlots->SetUserAtSlot(TestSlot, FakeAccessToken, ReplacementRefreshToken, FakeExpiresIn, FakeCid, FakePid);
			bFound = BeamUserSlots->GetUserDataWithRefreshTokenAndPid(ReplacementRefreshToken, FakePid, RealmUser, UserSlot);

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
			BeamUserSlots->SaveUserAtSlot(TestSlot, FakeAccessToken, FakeRefreshToken, FakeExpiresIn, FakeCid, FakePid);

			FBeamRealmUser RealmUser;
			auto bFound = BeamUserSlots->GetUserDataAtSlot(TestSlot, RealmUser);
			TestTrue("found user", bFound);

			IFileManager& FileManager = IFileManager::Get();
			FileManager.FileExists(*BeamUserSlots->GetSavedSlotPath(TestSlot));

			// Clear the slot so we can verify the loading function actually works
			BeamUserSlots->SetUserAtSlot(TestSlot, TEXT(""), TEXT(""), 0, TEXT(""),TEXT(""));

			// Load the user from the serialized file and see if it was loaded correctly.
			const auto bLoaded = BeamUserSlots->TryLoadSavedUserAtSlot(TestSlot);
			bFound = BeamUserSlots->GetUserDataAtSlot(TestSlot, RealmUser);

			TestTrue("successfully added user to slot", bFound);
			TestTrue("successfully added user to slot from serialized user file", bLoaded);
			TestTrue("added correct user data to slot", RealmUser.AuthToken.AccessToken == FakeAccessToken);
			TestTrue("added correct user data to slot", RealmUser.AuthToken.RefreshToken == FakeRefreshToken);
			TestTrue("added correct user data to slot", RealmUser.AuthToken.ExpiresIn == FakeExpiresIn);

			TestTrue("added correct user data to slot", RealmUser.RealmHandle.Cid == FakeCid);
			TestTrue("added correct user data to slot", RealmUser.RealmHandle.Pid == FakePid);
		});

		It("should fail gracefully when trying to load an unsaved UserSlot", [=, this]()
		{
			// Tries to load the user from a non-existing Saved UserSlot and sees if it gracefully returns false.
			const auto bLoaded = BeamUserSlots->TryLoadSavedUserAtSlot(TestSlot);
			TestTrue("failed to add user to slot since no saved user existed at that slot", !bLoaded);
		});

		It("should save a user and then clear them BUT don't clear the saved used", [=, this]()
		{
			BeamUserSlots->SaveUserAtSlot(TestSlot, FakeAccessToken, FakeRefreshToken, FakeExpiresIn, FakeCid, FakePid);

			FBeamRealmUser RealmUser;
			const auto bFound = BeamUserSlots->GetUserDataAtSlot(TestSlot, RealmUser);
			TestTrue("found user", bFound);

			const auto Handle = BeamUserSlots->GlobalUserSlotClearedCodeHandler.AddLambda([=, this]
			(const EUserSlotClearedReason& UserSlotClearedReason, const FUserSlot& UserSlot, const FBeamRealmUser& BeamRealmUser)
				{
					FBeamRealmUser RealmUserAfterClear;
					const auto bFoundAfterClear = BeamUserSlots->GetUserDataAtSlot(TestSlot, RealmUserAfterClear);
					TestTrue("failed to find user after clear", !bFoundAfterClear);

					// Test the clear parameters are forwarded correctly 
					TestTrue("Reason is what expected", UserSlotClearedReason == Manual);
					TestTrue("UserSlot is the cleared one", UserSlot == TestSlot);

					// Test that, even though we cleared the user, we still have access to the data at the moment of clearing
					TestTrue("Realm User has the correct data of the moment of clearing", BeamRealmUser.AuthToken.AccessToken == FakeAccessToken);
					TestTrue("Realm User has the correct data of the moment of clearing", BeamRealmUser.AuthToken.RefreshToken == FakeRefreshToken);
					TestTrue("Realm User has the correct data of the moment of clearing", BeamRealmUser.AuthToken.ExpiresIn == FakeExpiresIn);
					TestTrue("Realm User has the correct data of the moment of clearing", BeamRealmUser.RealmHandle.Cid == FakeCid);
					TestTrue("Realm User has the correct data of the moment of clearing", BeamRealmUser.RealmHandle.Pid == FakePid);
				});

			AddedTestHandlers.Add(Handle);

			// Clear the slot so we can verify the loading function actually works
			BeamUserSlots->ClearUserAtSlot(TestSlot, Manual, false);

			// Load the user from the serialized file and see if it was loaded correctly.
			FBeamRealmUser RealmUserAfterReload;
			const auto bLoaded = BeamUserSlots->TryLoadSavedUserAtSlot(TestSlot);
			const auto bFoundAfterReload = BeamUserSlots->GetUserDataAtSlot(TestSlot, RealmUserAfterReload);

			// Test that the serialized file was not cleared.
			TestTrue("successfully added user to slot", bFoundAfterReload);
			TestTrue("successfully added user to slot from serialized user file", bLoaded);
			TestTrue("added correct user data to slot", RealmUser.AuthToken.AccessToken == FakeAccessToken);
			TestTrue("added correct user data to slot", RealmUser.AuthToken.RefreshToken == FakeRefreshToken);
			TestTrue("added correct user data to slot", RealmUser.AuthToken.ExpiresIn == FakeExpiresIn);

			TestTrue("added correct user data to slot", RealmUser.RealmHandle.Cid == FakeCid);
			TestTrue("added correct user data to slot", RealmUser.RealmHandle.Pid == FakePid);
		});

		It("should save a user and then clear them AND clear the saved used", [=, this]()
		{
			BeamUserSlots->SaveUserAtSlot(TestSlot, FakeAccessToken, FakeRefreshToken, FakeExpiresIn, FakeCid, FakePid);

			FBeamRealmUser RealmUser;
			const auto bFound = BeamUserSlots->GetUserDataAtSlot(TestSlot, RealmUser);
			TestTrue("found user", bFound);

			const auto Handle = BeamUserSlots->GlobalUserSlotClearedCodeHandler.AddLambda([=, this]
			(const EUserSlotClearedReason& UserSlotClearedReason, const FUserSlot& UserSlot, const FBeamRealmUser& BeamRealmUser)
				{
					FBeamRealmUser RealmUserAfterClear;
					const auto bFoundAfterClear = BeamUserSlots->GetUserDataAtSlot(TestSlot, RealmUserAfterClear);
					TestTrue("failed to find user after clear", !bFoundAfterClear);

					// Test the clear parameters are forwarded correctly 
					TestTrue("Reason is what expected", UserSlotClearedReason == Manual);
					TestTrue("UserSlot is the cleared one", UserSlot == TestSlot);

					// Test that, even though we cleared the user, we still have access to the data at the moment of clearing
					TestTrue("Realm User has the correct data of the moment of clearing", BeamRealmUser.AuthToken.AccessToken == FakeAccessToken);
					TestTrue("Realm User has the correct data of the moment of clearing", BeamRealmUser.AuthToken.RefreshToken == FakeRefreshToken);
					TestTrue("Realm User has the correct data of the moment of clearing", BeamRealmUser.AuthToken.ExpiresIn == FakeExpiresIn);
					TestTrue("Realm User has the correct data of the moment of clearing", BeamRealmUser.RealmHandle.Cid == FakeCid);
					TestTrue("Realm User has the correct data of the moment of clearing", BeamRealmUser.RealmHandle.Pid == FakePid);
				});
			AddedTestHandlers.Add(Handle);

			// Clear the slot so we can verify the loading function actually works
			BeamUserSlots->ClearUserAtSlot(TestSlot, Manual, true);

			// Load the user from the serialized file and see if it was loaded correctly.
			FBeamRealmUser RealmUserAfterReload;
			const auto bLoaded = BeamUserSlots->TryLoadSavedUserAtSlot(TestSlot);

			// Test that the serialized file was cleared.					
			TestTrue("successfully added user to slot from serialized user file", !bLoaded);
		});
	});
}
