#pragma once

#include "CoreMinimal.h"
#include "BeamCoreTypes.h"
#include "RawAPIs/BeamOptionalTypes.h"
#include "RawAPIs/BeamSharedTypes.h"

#include "BeamAuthApiModels.generated.h"


/**
 _____            _     _               _____          _                              _____                            _   
|  __ \          (_)   | |             / ____|        | |                            |  __ \                          | |  
| |__) |___  __ _ _ ___| |_ ___ _ __  | |    _   _ ___| |_ ___  _ __ ___   ___ _ __  | |__) |___  __ _ _   _  ___  ___| |_ 
|  _  // _ \/ _` | / __| __/ _ \ '__| | |   | | | / __| __/ _ \| '_ ` _ \ / _ \ '__| |  _  // _ \/ _` | | | |/ _ \/ __| __|
| | \ \  __/ (_| | \__ \ ||  __/ |    | |___| |_| \__ \ || (_) | | | | | |  __/ |    | | \ \  __/ (_| | |_| |  __/\__ \ |_ 
|_|  \_\___|\__, |_|___/\__\___|_|     \_____\__,_|___/\__\___/|_| |_| |_|\___|_|    |_|  \_\___|\__, |\__,_|\___||___/\__|
			__/ |                                                                                  | |                    
		   |___/                                                                                   |_|                    
*/

USTRUCT(BlueprintType)
struct BEAMABLECORE_API FRegisterCustomerRequestBody : public FBeamJsonSerializable
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Email;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Password;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString CustomerName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Alias;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString ProjectName;

	FRegisterCustomerRequestBody() = default;

	explicit FRegisterCustomerRequestBody(const FString& Email, const FString& Password, const FString& CustomerName, const FString& Alias, const FString& ProjectName)
		: Email(Email),
		  Password(Password),
		  CustomerName(CustomerName),
		  Alias(Alias),
		  ProjectName(ProjectName)
	{
	}

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& JsonString) override;
};


USTRUCT(BlueprintType)
struct BEAMABLECORE_API FRegisterCustomerResponseBody : public FBeamJsonSerializable
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	int64 CID;

	UPROPERTY(BlueprintReadOnly)
	FString PID;

	UPROPERTY(BlueprintReadOnly)
	FTokenResponse TokenResponse;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& JsonString) override;
};


USTRUCT(BlueprintType)
struct BEAMABLECORE_API FRegisterCustomerRequest : public FBeamBaseRequest
{
	GENERATED_BODY()

	// Non-Body Params go here (ALWAYS FLATTEN!)

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FRegisterCustomerRequestBody Body;

	FRegisterCustomerRequest() = default;

	explicit FRegisterCustomerRequest(FRegisterCustomerRequestBody Body): Body(Body)
	{
	}

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;
	
};

USTRUCT(BlueprintType)
struct FRegisterCustomerResponse : public FBeamBaseResponse
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FRegisterCustomerResponseBody Body;
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnRegisterCustomerSuccess, int64, RequestId, FRegisterCustomerRequest, Request, FRegisterCustomerResponse, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnRegisterCustomerError, int64, RequestId, FRegisterCustomerRequest, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnRegisterCustomerComplete, int64, RequestId, FRegisterCustomerRequest, Request);

using FRegisterCustomerFullResponse = FBeamFullResponse<FRegisterCustomerRequest, FRegisterCustomerResponse>;
DECLARE_DELEGATE_OneParam(FOnRegisterCustomerFullResponse, FRegisterCustomerFullResponse);

/**

 __  __        _____                            _   
|  \/  |      |  __ \                          | |  
| \  / | ___  | |__) |___  __ _ _   _  ___  ___| |_ 
| |\/| |/ _ \ |  _  // _ \/ _` | | | |/ _ \/ __| __|
| |  | |  __/ | | \ \  __/ (_| | |_| |  __/\__ \ |_ 
|_|  |_|\___| |_|  \_\___|\__, |\__,_|\___||___/\__|
												| |                    
												|_|                    

*/

USTRUCT(BlueprintType)
struct BEAMABLECORE_API FMeResponseBody : public FBeamJsonSerializable
{
	GENERATED_BODY()

	/// <summary>
	/// The unique id of the player, sometimes called a "dbid".
	/// </summary>
	UPROPERTY(BlueprintReadOnly)
	int64 Id;

	/// <summary>
	/// If the player has associated an email with their account, the email will appear here. Null otherwise.
	/// The email can be associated with the <see cref="IAuthApi.RegisterDBCredentials"/> method
	/// </summary>
	UPROPERTY(BlueprintReadOnly)
	FString Email;

	/// <summary>
	/// If the player has chosen a language for their account, the language code will appear here. EN by default.
	/// </summary>
	UPROPERTY(BlueprintReadOnly)
	FOptionalString Language;

	/// <summary>
	/// Scopes are permissions that the player has over the Beamable ecosystem.
	/// Most players will have no scopes.
	/// Players with the role of "tester" will have some "read" based scopes,
	/// Players with the role of "developer" will have most all scopes except those relating to team management, and
	/// Players with the role of "admin" will have single scope with the value of "*", which indicates ALL scopes.
	/// </summary>
	UPROPERTY(BlueprintReadOnly)
	TArray<FString> Scopes;

	/// <summary>
	/// If the player has associated any third party accounts with their account, those will appear here.
	/// The values of the strings will be taken from the <see cref="AuthThirdPartyMethods.GetString"/> method.
	/// Third parties can be associated with the <see cref="IAuthApi.RegisterThirdPartyCredentials"/> method.
	/// </summary>
	UPROPERTY(BlueprintReadOnly)
	TArray<FString> ThirdPartyAppAssociations;

	/// <summary>
	/// If the player has associated any device Ids with their account, those will appear here.
	/// </summary>
	UPROPERTY(BlueprintReadOnly)
	TArray<FString> DeviceIds;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
};


USTRUCT(BlueprintType)
struct BEAMABLECORE_API FMeRequest : public FBeamBaseRequest
{
	GENERATED_BODY()

	// Non-Body Params go here (ALWAYS FLATTEN!)
	FMeRequest() = default;	

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;
};

USTRUCT(BlueprintType)
struct FMeResponse : public FBeamBaseResponse
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FMeResponseBody Body;
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnMeSuccess, int64, RequestId, FMeRequest, Request, FMeResponse, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnMeError, int64, RequestId, FMeRequest, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnMeComplete, int64, RequestId, FMeRequest, Request);

using FMeFullResponse = FBeamFullResponse<FMeRequest, FMeResponse>;
DECLARE_DELEGATE_OneParam(FOnMeFullResponse, FMeFullResponse);


