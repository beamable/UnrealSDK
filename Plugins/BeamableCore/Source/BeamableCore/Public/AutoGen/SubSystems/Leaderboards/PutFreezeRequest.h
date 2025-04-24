
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "Serialization/BeamJsonUtils.h"
#include "BeamableCore/Public/AutoGen/CommonResponse.h"

#include "PutFreezeRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPutFreezeRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Object Id", Category="Beam")
	FString ObjectId = {};
	
	// Query Params
	

	// Body Params
	

	// Beam Base Request Declaration
	UPutFreezeRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Leaderboards|Utils|Make/Break", DisplayName="Make PutFreeze",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UPutFreezeRequest* Make(FString _ObjectId, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPutFreezeSuccess, FBeamRequestContext, Context, UPutFreezeRequest*, Request, UCommonResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPutFreezeError, FBeamRequestContext, Context, UPutFreezeRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPutFreezeComplete, FBeamRequestContext, Context, UPutFreezeRequest*, Request);

using FPutFreezeFullResponse = FBeamFullResponse<UPutFreezeRequest*, UCommonResponse*>;
DECLARE_DELEGATE_OneParam(FOnPutFreezeFullResponse, FPutFreezeFullResponse);
