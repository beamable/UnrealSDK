
#pragma once

#include "CoreMinimal.h"
#include "BeamCoreTypes.h"


#include "AutoGen/Group.h"

#include "ObjectGroupsGetGroupsRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UObjectGroupsGetGroupsRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Object Id")
	int64 ObjectId;
	
	// Query Params
	

	// Body Params
	

	// Beam Base Request Declaration
	UObjectGroupsGetGroupsRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer"))
	static UObjectGroupsGetGroupsRequest* MakeObjectGroupsGetGroupsRequest(int64 _ObjectId, UObject* Outer);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnObjectGroupsGetGroupsSuccess, FBeamRequestContext, Context, UObjectGroupsGetGroupsRequest*, Request, UGroup*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnObjectGroupsGetGroupsError, FBeamRequestContext, Context, UObjectGroupsGetGroupsRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnObjectGroupsGetGroupsComplete, FBeamRequestContext, Context, UObjectGroupsGetGroupsRequest*, Request);

using FObjectGroupsGetGroupsFullResponse = FBeamFullResponse<UObjectGroupsGetGroupsRequest*, UGroup*>;
DECLARE_DELEGATE_OneParam(FOnObjectGroupsGetGroupsFullResponse, FObjectGroupsGetGroupsFullResponse);
