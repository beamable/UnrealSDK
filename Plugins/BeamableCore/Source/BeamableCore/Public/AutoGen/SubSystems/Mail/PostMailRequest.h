
#pragma once

#include "CoreMinimal.h"
#include "BeamCoreTypes.h"


#include "AutoGen/SendMailObjectRequestBody.h"
#include "AutoGen/SendMailResponse.h"

#include "PostMailRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPostMailRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Object Id")
	int64 ObjectId;
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="")
	USendMailObjectRequestBody* Body;

	// Beam Base Request Declaration
	UPostMailRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, meta=(DefaultToSelf="Outer", AdvancedDisplay="_Body,_Expires,_PlayerRewards,_Subject,_Rewards,_Id,_BodyRef,_Attachments,Outer"))
	static UPostMailRequest* MakePostMailRequest(int64 _ObjectId, FOptionalString _Body, FOptionalString _Expires, FOptionalPlayerReward _PlayerRewards, FOptionalString _Subject, FOptionalMailRewards _Rewards, FOptionalInt64 _Id, int64 _SenderGamerTag, FString _Category, FOptionalInt64 _BodyRef, FOptionalArrayOfAttachmentRequestBody _Attachments, UObject* Outer);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostMailSuccess, FBeamRequestContext, Context, UPostMailRequest*, Request, USendMailResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostMailError, FBeamRequestContext, Context, UPostMailRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPostMailComplete, FBeamRequestContext, Context, UPostMailRequest*, Request);

using FPostMailFullResponse = FBeamFullResponse<UPostMailRequest*, USendMailResponse*>;
DECLARE_DELEGATE_OneParam(FOnPostMailFullResponse, FPostMailFullResponse);
