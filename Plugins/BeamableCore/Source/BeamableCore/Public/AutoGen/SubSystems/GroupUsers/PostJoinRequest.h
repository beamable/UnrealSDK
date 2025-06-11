
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "Serialization/BeamJsonUtils.h"
#include "BeamableCore/Public/AutoGen/GroupMembershipRequestBody.h"
#include "BeamableCore/Public/AutoGen/GroupMembershipResponse.h"

#include "PostJoinRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPostJoinRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Object Id", Category="Beam")
	int64 ObjectId = {};
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	UGroupMembershipRequestBody* Body = {};

	// Beam Base Request Declaration
	UPostJoinRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|GroupUsers|Utils|Make/Break", DisplayName="Make PostJoin",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="_Successor,_Score,_SubGroup,RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UPostJoinRequest* Make(int64 _ObjectId, EBeamGroupType _Type, int64 _Group, FOptionalInt64 _Successor, FOptionalInt64 _Score, FOptionalInt64 _SubGroup, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostJoinSuccess, FBeamRequestContext, Context, UPostJoinRequest*, Request, UGroupMembershipResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostJoinError, FBeamRequestContext, Context, UPostJoinRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPostJoinComplete, FBeamRequestContext, Context, UPostJoinRequest*, Request);

using FPostJoinFullResponse = FBeamFullResponse<UPostJoinRequest*, UGroupMembershipResponse*>;
DECLARE_DELEGATE_OneParam(FOnPostJoinFullResponse, FPostJoinFullResponse);
