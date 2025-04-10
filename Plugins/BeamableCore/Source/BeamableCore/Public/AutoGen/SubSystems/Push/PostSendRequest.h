
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableCore/Public/AutoGen/SendReq.h"
#include "BeamableCore/Public/AutoGen/EmptyRsp.h"

#include "PostSendRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPostSendRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	USendReq* Body = {};

	// Beam Base Request Declaration
	UPostSendRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Push|Utils|Make/Break", DisplayName="Make PostSend",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UPostSendRequest* Make(TArray<USendMsg*> _Msgs, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostSendSuccess, FBeamRequestContext, Context, UPostSendRequest*, Request, UEmptyRsp*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostSendError, FBeamRequestContext, Context, UPostSendRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPostSendComplete, FBeamRequestContext, Context, UPostSendRequest*, Request);

using FPostSendFullResponse = FBeamFullResponse<UPostSendRequest*, UEmptyRsp*>;
DECLARE_DELEGATE_OneParam(FOnPostSendFullResponse, FPostSendFullResponse);
