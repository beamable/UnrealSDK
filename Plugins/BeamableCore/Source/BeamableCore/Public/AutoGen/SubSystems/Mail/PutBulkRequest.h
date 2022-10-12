
#pragma once

#include "CoreMinimal.h"
#include "BeamCoreTypes.h"


#include "AutoGen/BulkUpdateMailObjectRequestBody.h"
#include "AutoGen/MailSuccessResponse.h"

#include "PutBulkRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPutBulkRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Object Id")
	int64 ObjectId;
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="")
	UBulkUpdateMailObjectRequestBody* Body;

	// Beam Base Request Declaration
	UPutBulkRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer"))
	static UPutBulkRequest* MakePutBulkRequest(int64 _ObjectId, TArray<UMyMailUpdate*> _UpdateMailRequests, UObject* Outer);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPutBulkSuccess, FBeamRequestContext, Context, UPutBulkRequest*, Request, UMailSuccessResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPutBulkError, FBeamRequestContext, Context, UPutBulkRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPutBulkComplete, FBeamRequestContext, Context, UPutBulkRequest*, Request);

using FPutBulkFullResponse = FBeamFullResponse<UPutBulkRequest*, UMailSuccessResponse*>;
DECLARE_DELEGATE_OneParam(FOnPutBulkFullResponse, FPutBulkFullResponse);
