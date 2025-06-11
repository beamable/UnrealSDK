
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableCore/Public/AutoGen/ConnectionString.h"

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

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Make GetStorageConnection",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UGetStorageConnectionRequest* Make(UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetStorageConnectionSuccess, FBeamRequestContext, Context, UGetStorageConnectionRequest*, Request, UConnectionString*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetStorageConnectionError, FBeamRequestContext, Context, UGetStorageConnectionRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnGetStorageConnectionComplete, FBeamRequestContext, Context, UGetStorageConnectionRequest*, Request);

using FGetStorageConnectionFullResponse = FBeamFullResponse<UGetStorageConnectionRequest*, UConnectionString*>;
DECLARE_DELEGATE_OneParam(FOnGetStorageConnectionFullResponse, FGetStorageConnectionFullResponse);
