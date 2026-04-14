
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableCore/Public/AutoGen/Optionals/OptionalString.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalInt32.h"
#include "BeamableCore/Public/AutoGen/AuthV2ListTokensResponse.h"

#include "ApiAuthGetTokensRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UApiAuthGetTokensRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Player Id Or Account Id", Category="Beam")
	FOptionalString PlayerIdOrAccountId = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Skip", Category="Beam")
	FOptionalInt32 Skip = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Limit", Category="Beam")
	FOptionalInt32 Limit = {};

	// Body Params
	

	// Beam Base Request Declaration
	UApiAuthGetTokensRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Auth|Utils|Make/Break", DisplayName="Make ApiAuthGetTokens",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="_PlayerIdOrAccountId,_Skip,_Limit,RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UApiAuthGetTokensRequest* Make(FOptionalString _PlayerIdOrAccountId, FOptionalInt32 _Skip, FOptionalInt32 _Limit, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnApiAuthGetTokensSuccess, FBeamRequestContext, Context, UApiAuthGetTokensRequest*, Request, UAuthV2ListTokensResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnApiAuthGetTokensError, FBeamRequestContext, Context, UApiAuthGetTokensRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnApiAuthGetTokensComplete, FBeamRequestContext, Context, UApiAuthGetTokensRequest*, Request);

using FApiAuthGetTokensFullResponse = FBeamFullResponse<UApiAuthGetTokensRequest*, UAuthV2ListTokensResponse*>;
DECLARE_DELEGATE_OneParam(FOnApiAuthGetTokensFullResponse, FApiAuthGetTokensFullResponse);
