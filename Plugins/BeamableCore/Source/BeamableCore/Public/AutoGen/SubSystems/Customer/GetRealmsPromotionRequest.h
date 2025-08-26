
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "Serialization/BeamJsonUtils.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalString.h"
#include "BeamableCore/Public/AutoGen/CustomerActorPromoteRealmResponse.h"

#include "GetRealmsPromotionRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UGetRealmsPromotionRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Customer Id", Category="Beam")
	FString CustomerId = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Destination Realm Id", Category="Beam")
	FString DestinationRealmId = {};
	
	// Query Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Source Realm Id", Category="Beam")
	FOptionalString SourceRealmId = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Promotables", Category="Beam")
	FOptionalString Promotables = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Content Ids", Category="Beam")
	FOptionalString ContentIds = {};

	// Body Params
	

	// Beam Base Request Declaration
	UGetRealmsPromotionRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Customer|Utils|Make/Break", DisplayName="Make GetRealmsPromotion",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="_SourceRealmId,_Promotables,_ContentIds,RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UGetRealmsPromotionRequest* Make(FString _CustomerId, FString _DestinationRealmId, FOptionalString _SourceRealmId, FOptionalString _Promotables, FOptionalString _ContentIds, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetRealmsPromotionSuccess, FBeamRequestContext, Context, UGetRealmsPromotionRequest*, Request, UCustomerActorPromoteRealmResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetRealmsPromotionError, FBeamRequestContext, Context, UGetRealmsPromotionRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnGetRealmsPromotionComplete, FBeamRequestContext, Context, UGetRealmsPromotionRequest*, Request);

using FGetRealmsPromotionFullResponse = FBeamFullResponse<UGetRealmsPromotionRequest*, UCustomerActorPromoteRealmResponse*>;
DECLARE_DELEGATE_OneParam(FOnGetRealmsPromotionFullResponse, FGetRealmsPromotionFullResponse);
