
#pragma once

#include "CoreMinimal.h"
#include "BeamCoreTypes.h"

#include "AutoGen/ConnectionString.h"

#include "GetStorageConnectionRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UGetStorageConnectionRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	

	// Beam Base Request Declaration
	UGetStorageConnectionRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer"))
	static UGetStorageConnectionRequest* MakeGetStorageConnectionRequest(UObject* Outer);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetStorageConnectionSuccess, FBeamRequestContext, Context, UGetStorageConnectionRequest*, Request, UConnectionString*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetStorageConnectionError, FBeamRequestContext, Context, UGetStorageConnectionRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnGetStorageConnectionComplete, FBeamRequestContext, Context, UGetStorageConnectionRequest*, Request);

using FGetStorageConnectionFullResponse = FBeamFullResponse<UGetStorageConnectionRequest*, UConnectionString*>;
DECLARE_DELEGATE_OneParam(FOnGetStorageConnectionFullResponse, FGetStorageConnectionFullResponse);
