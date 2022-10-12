
#pragma once

#include "CoreMinimal.h"
#include "BeamCoreTypes.h"


#include "AutoGen/Optionals/OptionalBool.h"
#include "AutoGen/AnnouncementQueryResponse.h"

#include "GetAnnouncementsRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UGetAnnouncementsRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Object Id")
	int64 ObjectId;
	
	// Query Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="B Include Deleted")
	FOptionalBool bIncludeDeleted;

	// Body Params
	

	// Beam Base Request Declaration
	UGetAnnouncementsRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, meta=(DefaultToSelf="Outer", AdvancedDisplay="_bIncludeDeleted,Outer"))
	static UGetAnnouncementsRequest* MakeGetAnnouncementsRequest(int64 _ObjectId, FOptionalBool _bIncludeDeleted, UObject* Outer);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetAnnouncementsSuccess, FBeamRequestContext, Context, UGetAnnouncementsRequest*, Request, UAnnouncementQueryResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetAnnouncementsError, FBeamRequestContext, Context, UGetAnnouncementsRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnGetAnnouncementsComplete, FBeamRequestContext, Context, UGetAnnouncementsRequest*, Request);

using FGetAnnouncementsFullResponse = FBeamFullResponse<UGetAnnouncementsRequest*, UAnnouncementQueryResponse*>;
DECLARE_DELEGATE_OneParam(FOnGetAnnouncementsFullResponse, FGetAnnouncementsFullResponse);
