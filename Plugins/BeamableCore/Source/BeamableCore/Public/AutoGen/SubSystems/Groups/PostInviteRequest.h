
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"


#include "BeamableCore/Public/AutoGen/GroupInvite.h"
#include "BeamableCore/Public/AutoGen/CommonResponse.h"

#include "PostInviteRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPostInviteRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Object Id", Category="Beam")
	int64 ObjectId;
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	UGroupInvite* Body;

	// Beam Base Request Declaration
	UPostInviteRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Backend|Groups", DisplayName="Beam - Make PostInvite",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="_SubGroup,_bUseNewRewardsSystem,RequestOwner"))
	static UPostInviteRequest* Make(int64 _ObjectId, int64 _GamerTag, FOptionalInt64 _SubGroup, FOptionalBool _bUseNewRewardsSystem, UObject* RequestOwner);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostInviteSuccess, FBeamRequestContext, Context, UPostInviteRequest*, Request, UCommonResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostInviteError, FBeamRequestContext, Context, UPostInviteRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPostInviteComplete, FBeamRequestContext, Context, UPostInviteRequest*, Request);

using FPostInviteFullResponse = FBeamFullResponse<UPostInviteRequest*, UCommonResponse*>;
DECLARE_DELEGATE_OneParam(FOnPostInviteFullResponse, FPostInviteFullResponse);
