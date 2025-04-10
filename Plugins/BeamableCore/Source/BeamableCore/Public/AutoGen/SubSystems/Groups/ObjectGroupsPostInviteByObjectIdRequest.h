
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "Serialization/BeamJsonUtils.h"
#include "BeamableCore/Public/AutoGen/GroupInvite.h"
#include "BeamableCore/Public/AutoGen/CommonResponse.h"

#include "ObjectGroupsPostInviteByObjectIdRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UObjectGroupsPostInviteByObjectIdRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Object Id", Category="Beam")
	int64 ObjectId = {};
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	UGroupInvite* Body = {};

	// Beam Base Request Declaration
	UObjectGroupsPostInviteByObjectIdRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Groups|Utils|Make/Break", DisplayName="Make ObjectGroupsPostInviteByObjectId",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="_SubGroup,_bUseNewRewardsSystem,RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UObjectGroupsPostInviteByObjectIdRequest* Make(int64 _ObjectId, int64 _GamerTag, FOptionalInt64 _SubGroup, FOptionalBool _bUseNewRewardsSystem, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnObjectGroupsPostInviteByObjectIdSuccess, FBeamRequestContext, Context, UObjectGroupsPostInviteByObjectIdRequest*, Request, UCommonResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnObjectGroupsPostInviteByObjectIdError, FBeamRequestContext, Context, UObjectGroupsPostInviteByObjectIdRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnObjectGroupsPostInviteByObjectIdComplete, FBeamRequestContext, Context, UObjectGroupsPostInviteByObjectIdRequest*, Request);

using FObjectGroupsPostInviteByObjectIdFullResponse = FBeamFullResponse<UObjectGroupsPostInviteByObjectIdRequest*, UCommonResponse*>;
DECLARE_DELEGATE_OneParam(FOnObjectGroupsPostInviteByObjectIdFullResponse, FObjectGroupsPostInviteByObjectIdFullResponse);
