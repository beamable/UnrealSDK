
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "Serialization/BeamJsonUtils.h"
#include "BeamableCore/Public/AutoGen/Group.h"

#include "ObjectGroupsGetGroupsByObjectIdRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UObjectGroupsGetGroupsByObjectIdRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Object Id", Category="Beam")
	int64 ObjectId = {};
	
	// Query Params
	

	// Body Params
	

	// Beam Base Request Declaration
	UObjectGroupsGetGroupsByObjectIdRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Groups|Utils|Make/Break", DisplayName="Make ObjectGroupsGetGroupsByObjectId",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UObjectGroupsGetGroupsByObjectIdRequest* Make(int64 _ObjectId, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnObjectGroupsGetGroupsByObjectIdSuccess, FBeamRequestContext, Context, UObjectGroupsGetGroupsByObjectIdRequest*, Request, UGroup*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnObjectGroupsGetGroupsByObjectIdError, FBeamRequestContext, Context, UObjectGroupsGetGroupsByObjectIdRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnObjectGroupsGetGroupsByObjectIdComplete, FBeamRequestContext, Context, UObjectGroupsGetGroupsByObjectIdRequest*, Request);

using FObjectGroupsGetGroupsByObjectIdFullResponse = FBeamFullResponse<UObjectGroupsGetGroupsByObjectIdRequest*, UGroup*>;
DECLARE_DELEGATE_OneParam(FOnObjectGroupsGetGroupsByObjectIdFullResponse, FObjectGroupsGetGroupsByObjectIdFullResponse);
