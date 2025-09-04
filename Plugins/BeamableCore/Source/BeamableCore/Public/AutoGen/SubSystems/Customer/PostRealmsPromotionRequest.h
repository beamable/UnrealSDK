
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "Serialization/BeamJsonUtils.h"
#include "BeamableCore/Public/AutoGen/CustomerActorPromoteRealmRequestBody.h"
#include "BeamableCore/Public/AutoGen/CustomerActorPromoteRealmResponse.h"

#include "PostRealmsPromotionRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPostRealmsPromotionRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Customer Id", Category="Beam")
	FString CustomerId = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Destination Realm Id", Category="Beam")
	FString DestinationRealmId = {};
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	UCustomerActorPromoteRealmRequestBody* Body = {};

	// Beam Base Request Declaration
	UPostRealmsPromotionRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Customer|Utils|Make/Break", DisplayName="Make PostRealmsPromotion",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="_Promotions,_ContentManifestIds,RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UPostRealmsPromotionRequest* Make(FString _CustomerId, FString _DestinationRealmId, FString _SourceRealmId, FOptionalArrayOfBeamPromotableType _Promotions, FOptionalArrayOfString _ContentManifestIds, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostRealmsPromotionSuccess, FBeamRequestContext, Context, UPostRealmsPromotionRequest*, Request, UCustomerActorPromoteRealmResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostRealmsPromotionError, FBeamRequestContext, Context, UPostRealmsPromotionRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPostRealmsPromotionComplete, FBeamRequestContext, Context, UPostRealmsPromotionRequest*, Request);

using FPostRealmsPromotionFullResponse = FBeamFullResponse<UPostRealmsPromotionRequest*, UCustomerActorPromoteRealmResponse*>;
DECLARE_DELEGATE_OneParam(FOnPostRealmsPromotionFullResponse, FPostRealmsPromotionFullResponse);
