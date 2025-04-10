
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "Serialization/BeamJsonUtils.h"
#include "BeamableCore/Public/AutoGen/SendMailObjectRequestBody.h"
#include "BeamableCore/Public/AutoGen/SendMailResponse.h"

#include "PostMailRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPostMailRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Object Id", Category="Beam")
	int64 ObjectId = {};
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	USendMailObjectRequestBody* Body = {};

	// Beam Base Request Declaration
	UPostMailRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Mail|Utils|Make/Break", DisplayName="Make PostMail",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="_Body,_Expires,_PlayerRewards,_Subject,_Rewards,_Id,_BodyRef,_Attachments,RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UPostMailRequest* Make(int64 _ObjectId, int64 _SenderGamerTag, FString _Category, FOptionalString _Body, FOptionalString _Expires, FOptionalPlayerReward _PlayerRewards, FOptionalString _Subject, FOptionalMailRewards _Rewards, FOptionalInt64 _Id, FOptionalInt64 _BodyRef, FOptionalArrayOfAttachmentRequestBody _Attachments, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostMailSuccess, FBeamRequestContext, Context, UPostMailRequest*, Request, USendMailResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostMailError, FBeamRequestContext, Context, UPostMailRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPostMailComplete, FBeamRequestContext, Context, UPostMailRequest*, Request);

using FPostMailFullResponse = FBeamFullResponse<UPostMailRequest*, USendMailResponse*>;
DECLARE_DELEGATE_OneParam(FOnPostMailFullResponse, FPostMailFullResponse);
