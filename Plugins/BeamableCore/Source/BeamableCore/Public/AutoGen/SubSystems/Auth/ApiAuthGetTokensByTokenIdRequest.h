
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "Serialization/BeamJsonUtils.h"
#include "BeamableCore/Public/AutoGen/AuthV2RefreshToken.h"

#include "ApiAuthGetTokensByTokenIdRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UApiAuthGetTokensByTokenIdRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Token Id", Category="Beam")
	FString TokenId = {};
	
	// Query Params
	

	// Body Params
	

	// Beam Base Request Declaration
	UApiAuthGetTokensByTokenIdRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Auth|Utils|Make/Break", DisplayName="Make ApiAuthGetTokensByTokenId",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UApiAuthGetTokensByTokenIdRequest* Make(FString _TokenId, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnApiAuthGetTokensByTokenIdSuccess, FBeamRequestContext, Context, UApiAuthGetTokensByTokenIdRequest*, Request, UAuthV2RefreshToken*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnApiAuthGetTokensByTokenIdError, FBeamRequestContext, Context, UApiAuthGetTokensByTokenIdRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnApiAuthGetTokensByTokenIdComplete, FBeamRequestContext, Context, UApiAuthGetTokensByTokenIdRequest*, Request);

using FApiAuthGetTokensByTokenIdFullResponse = FBeamFullResponse<UApiAuthGetTokensByTokenIdRequest*, UAuthV2RefreshToken*>;
DECLARE_DELEGATE_OneParam(FOnApiAuthGetTokensByTokenIdFullResponse, FApiAuthGetTokensByTokenIdFullResponse);
