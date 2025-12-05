package com.epicgames.unreal;

import android.app.Activity;
import android.content.Intent;
import android.content.pm.PackageInfo;
import android.content.pm.PackageManager;
import android.content.pm.Signature;
import android.util.Base64;

import androidx.annotation.NonNull;
import androidx.core.content.ContextCompat;
import androidx.credentials.ClearCredentialStateRequest;
import androidx.credentials.Credential;
import androidx.credentials.CredentialManager;
import androidx.credentials.CredentialManagerCallback;
import androidx.credentials.CustomCredential;
import androidx.credentials.GetCredentialRequest;
import androidx.credentials.GetCredentialResponse;
import androidx.credentials.exceptions.ClearCredentialException;
import androidx.credentials.exceptions.GetCredentialException;
import androidx.credentials.exceptions.NoCredentialException;

import com.google.android.gms.auth.api.identity.AuthorizationRequest;
import com.google.android.gms.auth.api.identity.AuthorizationResult;
import com.google.android.gms.auth.api.identity.Identity;
import com.google.android.gms.common.api.ApiException;
import com.google.android.gms.common.api.CommonStatusCodes;
import com.google.android.gms.common.api.Scope;
import com.google.android.libraries.identity.googleid.GetGoogleIdOption;
import com.google.android.libraries.identity.googleid.GoogleIdTokenCredential;

import java.security.MessageDigest;
import java.util.ArrayList;
import java.util.List;

public class GoogleLogin
{
	// Responses supported by this class
	public static final int GOOGLE_RESPONSE_OK = 0;
	public static final int GOOGLE_RESPONSE_CANCELED = 1;
	public static final int GOOGLE_RESPONSE_ERROR = 2;
	public static final int GOOGLE_RESPONSE_DEVELOPER_ERROR = 3;

	// Debug output tag
	private static final String TAG = "GOOGLE";

	// Owning activity
	final Activity Activity;

	// Output device for log messages.
	private final Logger GoogleLog;

	// Owned instance of the credential manager associated to the Acttivity
	final private CredentialManager CredentialMgr;

	// Oauth 2.0 client id for use in server to server communication(Obtained from Google Cloud console)
	private String ServerClientId;

	// Shold request offline access?
	boolean bRequestOfflineAccess = true;

	GoogleIdTokenCredential CurrentIdToken = null;
	
	private interface HandleLoginError
	{
		void Handle(GetCredentialException Error); 
	}

	public GoogleLogin(Activity InActivity)
	{
		Activity = InActivity;
		GoogleLog = new Logger("UE", TAG);
		CredentialMgr = CredentialManager.create(Activity);
	}

	@SuppressWarnings("unused")
	public boolean Init(String InServerClientId, boolean bInRequestServerAuthCode)
	{
		if (InServerClientId == null || InServerClientId.isEmpty())
		{
			GoogleLog.warn("Expected non empty ServerClientId to request id token. Id token to use serverside won't be available");
			return false;
		}
		else
		{
			ServerClientId = InServerClientId;
			bRequestOfflineAccess = bInRequestServerAuthCode;
			return true;
		}
	}

	@SuppressWarnings("unused")
	public void Login(String[] ScopeFields)
	{
		// Attempt login with already authorized credentials
		LoginImplementation(ScopeFields, true, ErrorOnAutomaticAttempt ->
		{
			if (ErrorOnAutomaticAttempt instanceof NoCredentialException) 
			{
				// Show UI to attempt login with any known account
				LoginImplementation(ScopeFields, false, this::SignInFailed);
			}
			else
			{
				SignInFailed(ErrorOnAutomaticAttempt);
			}
		});
	}

	private void LoginImplementation(String[] ScopeFields, boolean FilterByAuthorizedAccounts, HandleLoginError ErrorHandler)
	{
		GetGoogleIdOption GoogleIdOption = new GetGoogleIdOption.Builder()
			.setFilterByAuthorizedAccounts(FilterByAuthorizedAccounts)
			.setServerClientId(ServerClientId)
			.setAutoSelectEnabled(true)
			//.setNonce(NONCE)
			.build();

		GetCredentialRequest Request = new GetCredentialRequest.Builder()
			.addCredentialOption(GoogleIdOption)
			.build();

		CredentialMgr.getCredentialAsync(
			Activity,
			Request,
			null,
			ContextCompat.getMainExecutor(Activity),
			new CredentialManagerCallback<GetCredentialResponse, GetCredentialException>()
			{
				@Override
				public void onResult(GetCredentialResponse Result)
				{
					SignInSucceeded(Result, ScopeFields);
				}
				@Override
				public void onError(@NonNull GetCredentialException Error)
				{
					ErrorHandler.Handle(Error);
				}
			});
	}
	
	@SuppressWarnings("unused")
	public void Logout()
	{
		GoogleLog.debug("Logout started");

		CredentialMgr.clearCredentialStateAsync(new ClearCredentialStateRequest(),
			null,
			ContextCompat.getMainExecutor(Activity),
			new CredentialManagerCallback<Void, ClearCredentialException>() 
			{
				@Override
				public void onResult(Void Unused) 
				{
					nativeLogoutComplete(GOOGLE_RESPONSE_OK);
				}

				@Override
				public void onError(@NonNull ClearCredentialException Error) 
				{
					GoogleLog.error("Could not clear credentials: " + Error.getMessage());
					nativeLogoutComplete(GOOGLE_RESPONSE_ERROR);
				}
			}
		);
	}

	private void SignInSucceeded(GetCredentialResponse LoginResult, String[] ScopesToRequest)
	{
		GoogleLog.debug("Sign in succeeded");

		// Handle the successfully returned credential.
		Credential Credential = LoginResult.getCredential();
		if (Credential instanceof CustomCredential) 
		{
			if (GoogleIdTokenCredential.TYPE_GOOGLE_ID_TOKEN_CREDENTIAL.equals(Credential.getType())) 
			{
				GoogleIdTokenCredential IdTokenCredential = GoogleIdTokenCredential.createFrom(Credential.getData());
				PrintUserAccountInfo(IdTokenCredential);
				
				CurrentIdToken = IdTokenCredential;

				// Request scopes
				if (ScopesToRequest == null || ScopesToRequest.length == 0) 
				{
					NotifyLoginSuccess(null);
				}
				else
				{
					RequestScopes(ScopesToRequest);
				}
			} 
			else 
			{
				GoogleLog.error("Unexpected type of credential received");
				nativeLoginFailed(GOOGLE_RESPONSE_ERROR);
			}
		} 
		else 
		{
			GoogleLog.error("Unexpected type of credential received");
			nativeLoginFailed(GOOGLE_RESPONSE_ERROR);
		}
	}
	
	private void RequestScopes(String[] ScopesToRequest)
	{
		List<Scope> RequestedScopes = new ArrayList<>();
		for (String Scope : ScopesToRequest)
		{
			RequestedScopes.add(new Scope(Scope));
		}

		AuthorizationRequest.Builder RequestBuilder = AuthorizationRequest.builder().setRequestedScopes(RequestedScopes);
		if (bRequestOfflineAccess)
		{
			RequestBuilder.requestOfflineAccess(ServerClientId);
		}
		AuthorizationRequest Request = RequestBuilder.build();

		Identity.getAuthorizationClient(Activity)
			.authorize(Request)
			.addOnSuccessListener(
				AuthorizationResult -> 
				{
					if (AuthorizationResult.hasResolution()) 
					{
						// Access needs to be granted by the user
						try 
						{
							Activity.startIntentSenderForResult(AuthorizationResult.getPendingIntent().getIntentSender(), GameActivity.REQUEST_CODE_OSSGOOGLE_LOGIN, null, 0, 0, 0, null);
						} 
						catch (Exception Error) 
						{
							GoogleLog.error("Couldn't start Authorization UI");
							SignInFailed(Error);
						}
					} 
					else 
					{
						// Access already granted, continue with user action
						NotifyLoginSuccess(AuthorizationResult.getServerAuthCode());
					}
				})
			.addOnFailureListener(this::SignInFailed);
	}

	public void onActivityResult(int ResultCode, Intent Data)
	{
		// Result returned from launching the Intent from GoogleSignInApi.getSignInIntent(...);
		GoogleLog.debug("onActivityResult: Result " + ResultCode + " Data: " + ((Data != null) ? Data.toString() : "null"));

		try 
		{
			AuthorizationResult Result = Identity.getAuthorizationClient(Activity).getAuthorizationResultFromIntent(Data);
			NotifyLoginSuccess(Result.getServerAuthCode());
		} 
		catch (ApiException Error) 
		{
			SignInFailed(Error);
		}

		GoogleLog.debug("onActivityResult end");
	}

	private void NotifyLoginSuccess(String ServerAuthCode) 
	{
		String PhotoUrl = null;
		if (CurrentIdToken.getProfilePictureUri() != null)
		{
			PhotoUrl = CurrentIdToken.getProfilePictureUri().toString();
		}

		nativeLoginSuccess(CurrentIdToken.getId(), CurrentIdToken.getGivenName(), CurrentIdToken.getFamilyName(), CurrentIdToken.getDisplayName(), PhotoUrl, CurrentIdToken.getIdToken(), ServerAuthCode);
		CurrentIdToken = null;
	}

	private void SignInFailed(Exception Error)
	{
		CurrentIdToken = null;
		if (Error instanceof GetCredentialException)
		{
			GetCredentialException Exception = (GetCredentialException)Error;
			GoogleLog.warn("Sign in failed: Type: " +  Exception.getType() + "ErrorMessage: " + Exception.getMessage());

			if ( Exception.getType().equals(android.credentials.GetCredentialException.TYPE_USER_CANCELED))
			{
				nativeLoginFailed(GOOGLE_RESPONSE_CANCELED);
			}
			else
			{
				nativeLoginFailed(GOOGLE_RESPONSE_ERROR);
			}
		}
		else if (Error instanceof ApiException)
		{
			ApiException Exception = (ApiException)Error;
			GoogleLog.warn("Sign in failed: Type: ApiException Status code: " + Exception.getStatusCode() + " StatusMessage: " + Exception.getStatus().getStatusMessage());

			if ( Exception.getStatus().isCanceled())
			{
				nativeLoginFailed(GOOGLE_RESPONSE_CANCELED);
			}
			else if (Exception.getStatus().getStatusCode() == CommonStatusCodes.DEVELOPER_ERROR)
			{
				LogDeveloperError();
				nativeLoginFailed(GOOGLE_RESPONSE_DEVELOPER_ERROR);
			}
			else
			{
				nativeLoginFailed(GOOGLE_RESPONSE_ERROR);
			}
		}
		else
		{
			GoogleLog.warn("Sign in failed. ErrorMessage: " + Error.getMessage());
			nativeLoginFailed(GOOGLE_RESPONSE_ERROR);
		}
	}

	private void PrintUserAccountInfo(GoogleIdTokenCredential IdToken)
	{
		if (IdToken != null)
		{
			GoogleLog.debug("User Details:");
			GoogleLog.debug("    DisplayName:" + IdToken.getDisplayName());
			GoogleLog.debug("    Id:" + IdToken.getId());
			GoogleLog.debug("    IdToken:" + IdToken.getIdToken());
		}
		else
		{
			GoogleLog.debug("IdToken is null");
		}
	}

	private void LogDeveloperError()
	{
		GoogleLog.error("Sign in failed with DEVELOPER_ERROR status code. Is the apk signed with the certificate expected by the Oauth 2.0 client id associated to your app in Google Cloud Console?");
		String PackageName = Activity.getPackageName();
		GoogleLog.error("PackageName: " + PackageName);
		try
		{
			PackageInfo Info = Activity.getPackageManager().getPackageInfo(PackageName, PackageManager.GET_SIGNATURES);
			for (Signature Signature : Info.signatures)
			{
				MessageDigest Digest = MessageDigest.getInstance("SHA");
				Digest.update(Signature.toByteArray());
				GoogleLog.error("Signing certificate signature: " + Base64.encodeToString(Digest.digest(), Base64.DEFAULT));
			}
		}
		catch (Exception Ex)
		{
			GoogleLog.error("Could not get signature:" + Ex);
		}
	}

	private native void nativeLoginSuccess(String InUserId, String InGivenName, String InFamilyName, String InDisplayName, String InPhotoUrl, String InIdToken, String InServerAuthCode);
	private native void nativeLoginFailed(int ResponseCode);
	private native void nativeLogoutComplete(int ResponseCode);
}
