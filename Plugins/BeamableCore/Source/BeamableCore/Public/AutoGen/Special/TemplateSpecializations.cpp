#include "BeamBackend/BeamBackend.h"
#include "AutoGen/SubSystems/Beamo/PostMetricsUrlRequest.h"
#include "AutoGen/SubSystems/Beamo/GetStoragePerformanceRequest.h"
#include "AutoGen/SubSystems/Beamo/GetManifestsRequest.h"
#include "AutoGen/SubSystems/Beamo/GetTemplatesRequest.h"
#include "AutoGen/SubSystems/Beamo/PostLogsUrlRequest.h"
#include "AutoGen/SubSystems/Beamo/GetUploadAPIRequest.h"
#include "AutoGen/SubSystems/Beamo/GetStatusRequest.h"
#include "AutoGen/SubSystems/Beamo/GetManifestCurrentRequest.h"
#include "AutoGen/SubSystems/Beamo/PostManifestPullRequest.h"
#include "AutoGen/SubSystems/Beamo/GetRegistryRequest.h"
#include "AutoGen/SubSystems/Beamo/PostManifestDeployRequest.h"
#include "AutoGen/SubSystems/Beamo/GetStorageConnectionRequest.h"
#include "AutoGen/SubSystems/Beamo/GetManifestRequest.h"
#include "AutoGen/SubSystems/Beamo/PostManifestRequest.h"
#include "AutoGen/SubSystems/EventPlayers/GetEventPlayersRequest.h"
#include "AutoGen/SubSystems/EventPlayers/ObjectEventPlayersPostClaimRequest.h"
#include "AutoGen/SubSystems/EventPlayers/PutScoreRequest.h"
#include "AutoGen/SubSystems/Events/GetRunningRequest.h"
#include "AutoGen/SubSystems/Events/BasicEventsGetContentRequest.h"
#include "AutoGen/SubSystems/Events/GetCalendarRequest.h"
#include "AutoGen/SubSystems/Events/PostApplyContentRequest.h"
#include "AutoGen/SubSystems/Events/PutEndPhaseRequest.h"
#include "AutoGen/SubSystems/Events/GetEventsRequest.h"
#include "AutoGen/SubSystems/Events/GetPingRequest.h"
#include "AutoGen/SubSystems/Events/PutContentRequest.h"
#include "AutoGen/SubSystems/Events/DeleteContentRequest.h"
#include "AutoGen/SubSystems/Events/PutRefreshRequest.h"
#include "AutoGen/SubSystems/GroupUsers/GetAvailabilityRequest.h"
#include "AutoGen/SubSystems/GroupUsers/GetRecommendedRequest.h"
#include "AutoGen/SubSystems/GroupUsers/PostJoinRequest.h"
#include "AutoGen/SubSystems/GroupUsers/DeleteJoinRequest.h"
#include "AutoGen/SubSystems/GroupUsers/PostGroupRequest.h"
#include "AutoGen/SubSystems/GroupUsers/ObjectGroupUsersGetSearchRequest.h"
#include "AutoGen/SubSystems/GroupUsers/GetGroupUsersRequest.h"
#include "AutoGen/SubSystems/Groups/PostKickRequest.h"
#include "AutoGen/SubSystems/Groups/DeleteMemberRequest.h"
#include "AutoGen/SubSystems/Groups/ObjectGroupsGetGroupsRequest.h"
#include "AutoGen/SubSystems/Groups/PutGroupsRequest.h"
#include "AutoGen/SubSystems/Groups/DeleteGroupsRequest.h"
#include "AutoGen/SubSystems/Groups/ObjectGroupsPutRoleRequest.h"
#include "AutoGen/SubSystems/Groups/PostApplyRequest.h"
#include "AutoGen/SubSystems/Groups/PostDonationsRequest.h"
#include "AutoGen/SubSystems/Groups/PutDonationsRequest.h"
#include "AutoGen/SubSystems/Groups/PutDonationsClaimRequest.h"
#include "AutoGen/SubSystems/Groups/PostInviteRequest.h"
#include "AutoGen/SubSystems/Groups/PostPetitionRequest.h"
#include "AutoGen/SubSystems/Inventory/GetItemsRequest.h"
#include "AutoGen/SubSystems/Inventory/GetCurrencyRequest.h"
#include "AutoGen/SubSystems/Inventory/PutPreviewRequest.h"
#include "AutoGen/SubSystems/Inventory/GetMultipliersRequest.h"
#include "AutoGen/SubSystems/Inventory/GetInventoryRequest.h"
#include "AutoGen/SubSystems/Inventory/PostInventoryRequest.h"
#include "AutoGen/SubSystems/Inventory/PutInventoryRequest.h"
#include "AutoGen/SubSystems/Inventory/DeleteTransactionRequest.h"
#include "AutoGen/SubSystems/Inventory/PutTransferRequest.h"
#include "AutoGen/SubSystems/Leaderboards/GetRanksRequest.h"
#include "AutoGen/SubSystems/Leaderboards/GetMatchesRequest.h"
#include "AutoGen/SubSystems/Leaderboards/PutEntryRequest.h"
#include "AutoGen/SubSystems/Leaderboards/GetViewRequest.h"
#include "AutoGen/SubSystems/Leaderboards/BasicLeaderboardsGetListRequest.h"
#include "AutoGen/SubSystems/Leaderboards/GetPlayerRequest.h"
#include "AutoGen/SubSystems/Leaderboards/BasicLeaderboardsGetAssignmentRequest.h"
#include "AutoGen/SubSystems/Leaderboards/GetUidRequest.h"
#include "AutoGen/SubSystems/Leaderboards/DeleteEntriesRequest.h"
#include "AutoGen/SubSystems/Leaderboards/GetMembershipRequest.h"
#include "AutoGen/SubSystems/Leaderboards/GetPartitionRequest.h"
#include "AutoGen/SubSystems/Leaderboards/GetFriendsRequest.h"
#include "AutoGen/SubSystems/Leaderboards/PostLeaderboardsRequest.h"
#include "AutoGen/SubSystems/Leaderboards/DeleteLeaderboardsRequest.h"
#include "AutoGen/SubSystems/Leaderboards/ObjectLeaderboardsGetAssignmentRequest.h"
#include "AutoGen/SubSystems/Leaderboards/DeleteAssignmentRequest.h"
#include "AutoGen/SubSystems/Leaderboards/DeleteEntryRequest.h"
#include "AutoGen/SubSystems/Leaderboards/PutFreezeRequest.h"
#include "AutoGen/SubSystems/Leaderboards/GetDetailsRequest.h"
#include "AutoGen/SubSystems/Leaderboards/PutSwapRequest.h"
#include "AutoGen/SubSystems/Accounts/GetGetPersonallyIdentifiableInformationRequest.h"
#include "AutoGen/SubSystems/Accounts/GetAvailableThirdPartyRequest.h"
#include "AutoGen/SubSystems/Accounts/PostPasswordUpdateInitRequest.h"
#include "AutoGen/SubSystems/Accounts/GetAvailableDeviceIdRequest.h"
#include "AutoGen/SubSystems/Accounts/GetAvailableRequest.h"
#include "AutoGen/SubSystems/Accounts/PostPasswordUpdateConfirmRequest.h"
#include "AutoGen/SubSystems/Accounts/GetAvailableRolesRequest.h"
#include "AutoGen/SubSystems/Accounts/DeleteMeDeviceRequest.h"
#include "AutoGen/SubSystems/Accounts/BasicAccountsGetMeRequest.h"
#include "AutoGen/SubSystems/Accounts/PutMeRequest.h"
#include "AutoGen/SubSystems/Accounts/DeleteMeThirdPartyRequest.h"
#include "AutoGen/SubSystems/Accounts/BasicAccountsGetSearchRequest.h"
#include "AutoGen/SubSystems/Accounts/PostEmailUpdateInitRequest.h"
#include "AutoGen/SubSystems/Accounts/PostEmailUpdateConfirmRequest.h"
#include "AutoGen/SubSystems/Accounts/PostAdminAdminUserRequest.h"
#include "AutoGen/SubSystems/Accounts/BasicAccountsPostRegisterRequest.h"
#include "AutoGen/SubSystems/Accounts/GetAdminMeRequest.h"
#include "AutoGen/SubSystems/Accounts/GetAdminAdminUsersRequest.h"
#include "AutoGen/SubSystems/Accounts/GetFindRequest.h"
#include "AutoGen/SubSystems/Accounts/PutAdminEmailRequest.h"
#include "AutoGen/SubSystems/Accounts/GetRoleReportRequest.h"
#include "AutoGen/SubSystems/Accounts/ObjectAccountsPutRoleRequest.h"
#include "AutoGen/SubSystems/Accounts/DeleteRoleRequest.h"
#include "AutoGen/SubSystems/Accounts/PutAdminScopeRequest.h"
#include "AutoGen/SubSystems/Accounts/DeleteAdminScopeRequest.h"
#include "AutoGen/SubSystems/Accounts/PutAdminThirdPartyRequest.h"
#include "AutoGen/SubSystems/Accounts/DeleteAdminThirdPartyRequest.h"
#include "AutoGen/SubSystems/Accounts/PutAccountsRequest.h"
#include "AutoGen/SubSystems/Accounts/DeleteAdminForgetRequest.h"
#include "AutoGen/SubSystems/Stats/GetClientBatchRequest.h"
#include "AutoGen/SubSystems/Stats/PostClientStringlistRequest.h"
#include "AutoGen/SubSystems/Stats/GetClientRequest.h"
#include "AutoGen/SubSystems/Stats/PostClientRequest.h"
#include "AutoGen/SubSystems/Stats/PutSubscribeRequest.h"
#include "AutoGen/SubSystems/Stats/PostBatchRequest.h"
#include "AutoGen/SubSystems/Stats/BasicStatsPostSearchRequest.h"
#include "AutoGen/SubSystems/Stats/PostSearchExtendedRequest.h"
#include "AutoGen/SubSystems/Stats/GetStatsRequest.h"
#include "AutoGen/SubSystems/Stats/PostStatsRequest.h"
#include "AutoGen/SubSystems/Stats/DeleteStatsRequest.h"
#include "AutoGen/SubSystems/Tournaments/PostSearchGroupsRequest.h"
#include "AutoGen/SubSystems/Tournaments/BasicTournamentsGetTournamentsRequest.h"
#include "AutoGen/SubSystems/Tournaments/PostScoreRequest.h"
#include "AutoGen/SubSystems/Tournaments/ObjectTournamentsGetTournamentsRequest.h"
#include "AutoGen/SubSystems/Tournaments/PostTournamentsRequest.h"
#include "AutoGen/SubSystems/Tournaments/GetMeGroupRequest.h"
#include "AutoGen/SubSystems/Tournaments/GetRewardsRequest.h"
#include "AutoGen/SubSystems/Tournaments/PostRewardsRequest.h"
#include "AutoGen/SubSystems/Tournaments/GetGlobalRequest.h"
#include "AutoGen/SubSystems/Tournaments/GetStandingsGroupRequest.h"
#include "AutoGen/SubSystems/Tournaments/GetStandingsRequest.h"
#include "AutoGen/SubSystems/Tournaments/GetAdminPlayerRequest.h"
#include "AutoGen/SubSystems/Tournaments/PutAdminPlayerRequest.h"
#include "AutoGen/SubSystems/Tournaments/BasicTournamentsGetMeRequest.h"
#include "AutoGen/SubSystems/Tournaments/GetChampionsRequest.h"
#include "AutoGen/SubSystems/Tournaments/BasicTournamentsGetGroupsRequest.h"
#include "AutoGen/SubSystems/Auth/GetTokenRequest.h"
#include "AutoGen/SubSystems/Auth/AuthenticateRequest.h"
#include "AutoGen/SubSystems/Auth/GetTokenListRequest.h"
#include "AutoGen/SubSystems/Auth/PutTokenRevokeRequest.h"
#include "AutoGen/SubSystems/Cloudsaving/GetCloudsavingRequest.h"
#include "AutoGen/SubSystems/Cloudsaving/PostDataReplaceRequest.h"
#include "AutoGen/SubSystems/Cloudsaving/DeleteDataRequest.h"
#include "AutoGen/SubSystems/Cloudsaving/PostDataDownloadURLRequest.h"
#include "AutoGen/SubSystems/Cloudsaving/GetDataMetadataRequest.h"
#include "AutoGen/SubSystems/Cloudsaving/PostDataDownloadURLFromPortalRequest.h"
#include "AutoGen/SubSystems/Cloudsaving/PutDataMoveRequest.h"
#include "AutoGen/SubSystems/Cloudsaving/PutDataMoveFromPortalRequest.h"
#include "AutoGen/SubSystems/Cloudsaving/PostDataUploadURLFromPortalRequest.h"
#include "AutoGen/SubSystems/Cloudsaving/PutDataCommitManifestRequest.h"
#include "AutoGen/SubSystems/Cloudsaving/PostDataUploadURLRequest.h"
#include "AutoGen/SubSystems/Payments/PostWindowsPurchaseTrackRequest.h"
#include "AutoGen/SubSystems/Payments/GetAuditsRequest.h"
#include "AutoGen/SubSystems/Payments/PostWindowsPurchaseCompleteRequest.h"
#include "AutoGen/SubSystems/Payments/GetFacebookUpdateRequest.h"
#include "AutoGen/SubSystems/Payments/PostFacebookUpdateRequest.h"
#include "AutoGen/SubSystems/Payments/PostFacebookPurchaseCompleteRequest.h"
#include "AutoGen/SubSystems/Payments/PostTestPurchaseCompleteRequest.h"
#include "AutoGen/SubSystems/Payments/GetItunesProductRequest.h"
#include "AutoGen/SubSystems/Payments/PostGoogleplayPurchaseCompleteRequest.h"
#include "AutoGen/SubSystems/Payments/PostTestPurchaseTrackRequest.h"
#include "AutoGen/SubSystems/Payments/PostGoogleplayPurchaseVerifyRequest.h"
#include "AutoGen/SubSystems/Payments/PostCouponPurchaseTrackRequest.h"
#include "AutoGen/SubSystems/Payments/PostSteamPurchaseCompleteRequest.h"
#include "AutoGen/SubSystems/Payments/PostFacebookPurchaseTrackRequest.h"
#include "AutoGen/SubSystems/Payments/PostTestPurchaseVerifyRequest.h"
#include "AutoGen/SubSystems/Payments/PostGoogleplayPurchaseTrackRequest.h"
#include "AutoGen/SubSystems/Payments/GetSteamPricesRequest.h"
#include "AutoGen/SubSystems/Payments/PostWindowsPurchaseVerifyRequest.h"
#include "AutoGen/SubSystems/Payments/PostItunesPurchaseVerifyRequest.h"
#include "AutoGen/SubSystems/Payments/PostItunesPurchaseCompleteRequest.h"
#include "AutoGen/SubSystems/Payments/PostFacebookPurchaseVerifyRequest.h"
#include "AutoGen/SubSystems/Payments/PostSteamPurchaseTrackRequest.h"
#include "AutoGen/SubSystems/Payments/PostCouponPurchaseVerifyRequest.h"
#include "AutoGen/SubSystems/Payments/GetWindowsProductRequest.h"
#include "AutoGen/SubSystems/Payments/GetFacebookProductRequest.h"
#include "AutoGen/SubSystems/Payments/GetCouponProductRequest.h"
#include "AutoGen/SubSystems/Payments/GetSteamProductsRequest.h"
#include "AutoGen/SubSystems/Payments/PostSteamAuthRequest.h"
#include "AutoGen/SubSystems/Payments/GetSteamProductRequest.h"
#include "AutoGen/SubSystems/Payments/PostCouponPurchaseCompleteRequest.h"
#include "AutoGen/SubSystems/Payments/GetGoogleplayProductRequest.h"
#include "AutoGen/SubSystems/Payments/GetTestProductRequest.h"
#include "AutoGen/SubSystems/Payments/PostSteamPurchaseVerifyRequest.h"
#include "AutoGen/SubSystems/Payments/PostItunesPurchaseTrackRequest.h"
#include "AutoGen/SubSystems/Payments/GetPaymentsRequest.h"
#include "AutoGen/SubSystems/Payments/PostTestPurchaseBeginRequest.h"
#include "AutoGen/SubSystems/Payments/PostSteamPurchaseFailRequest.h"
#include "AutoGen/SubSystems/Payments/PostFacebookPurchaseFailRequest.h"
#include "AutoGen/SubSystems/Payments/PostGoogleplayPurchaseBeginRequest.h"
#include "AutoGen/SubSystems/Payments/PostItunesPurchaseBeginRequest.h"
#include "AutoGen/SubSystems/Payments/PostFacebookPurchaseCancelRequest.h"
#include "AutoGen/SubSystems/Payments/PostItunesPurchaseFailRequest.h"
#include "AutoGen/SubSystems/Payments/PostTestPurchaseCancelRequest.h"
#include "AutoGen/SubSystems/Payments/PostTestPurchaseFailRequest.h"
#include "AutoGen/SubSystems/Payments/PostCouponPurchaseCancelRequest.h"
#include "AutoGen/SubSystems/Payments/PostCouponPurchaseBeginRequest.h"
#include "AutoGen/SubSystems/Payments/PostFacebookPurchaseBeginRequest.h"
#include "AutoGen/SubSystems/Payments/GetSteamOrderRequest.h"
#include "AutoGen/SubSystems/Payments/PostWindowsPurchaseBeginRequest.h"
#include "AutoGen/SubSystems/Payments/PostGoogleplayPurchaseFailRequest.h"
#include "AutoGen/SubSystems/Payments/PostGoogleplayPurchaseCancelRequest.h"
#include "AutoGen/SubSystems/Payments/PostCouponPurchaseFailRequest.h"
#include "AutoGen/SubSystems/Payments/PostSteamPurchaseBeginRequest.h"
#include "AutoGen/SubSystems/Payments/PostSteamPurchaseCancelRequest.h"
#include "AutoGen/SubSystems/Payments/PostWindowsPurchaseCancelRequest.h"
#include "AutoGen/SubSystems/Payments/PostWindowsPurchaseFailRequest.h"
#include "AutoGen/SubSystems/Payments/PostItunesPurchaseCancelRequest.h"
#include "AutoGen/SubSystems/Push/BasicPushPostRegisterRequest.h"
#include "AutoGen/SubSystems/Push/PostSendRequest.h"
#include "AutoGen/SubSystems/Notification/PostPlayerRequest.h"
#include "AutoGen/SubSystems/Notification/PostCustomRequest.h"
#include "AutoGen/SubSystems/Notification/PostServerRequest.h"
#include "AutoGen/SubSystems/Notification/PostGenericRequest.h"
#include "AutoGen/SubSystems/Notification/GetNotificationRequest.h"
#include "AutoGen/SubSystems/Notification/BasicNotificationPostGameRequest.h"
#include "AutoGen/SubSystems/Realms/GetCustomerAliasAvailableRequest.h"
#include "AutoGen/SubSystems/Realms/GetProjectRequest.h"
#include "AutoGen/SubSystems/Realms/PostCustomerRequest.h"
#include "AutoGen/SubSystems/Realms/GetIsCustomerRequest.h"
#include "AutoGen/SubSystems/Realms/GetCustomersRequest.h"
#include "AutoGen/SubSystems/Realms/PostProjectBeamableRequest.h"
#include "AutoGen/SubSystems/Realms/PostProjectRequest.h"
#include "AutoGen/SubSystems/Realms/PutProjectRequest.h"
#include "AutoGen/SubSystems/Realms/DeleteProjectRequest.h"
#include "AutoGen/SubSystems/Realms/GetGamesRequest.h"
#include "AutoGen/SubSystems/Realms/GetConfigRequest.h"
#include "AutoGen/SubSystems/Realms/PutConfigRequest.h"
#include "AutoGen/SubSystems/Realms/PutProjectRenameRequest.h"
#include "AutoGen/SubSystems/Realms/GetPlansRequest.h"
#include "AutoGen/SubSystems/Realms/PostPlansRequest.h"
#include "AutoGen/SubSystems/Realms/GetCustomerRequest.h"
#include "AutoGen/SubSystems/Realms/GetLaunchMessageRequest.h"
#include "AutoGen/SubSystems/Realms/PostLaunchMessageRequest.h"
#include "AutoGen/SubSystems/Realms/DeleteLaunchMessageRequest.h"
#include "AutoGen/SubSystems/Realms/GetAdminCustomerRequest.h"
#include "AutoGen/SubSystems/Realms/GetGameRequest.h"
#include "AutoGen/SubSystems/Realms/BasicRealmsPostGameRequest.h"
#include "AutoGen/SubSystems/Realms/PutGameRequest.h"
#include "AutoGen/SubSystems/Realms/GetProjectPromoteRequest.h"
#include "AutoGen/SubSystems/Realms/PostProjectPromoteRequest.h"
#include "AutoGen/SubSystems/Realms/GetPromotionRequest.h"
#include "AutoGen/SubSystems/Realms/PostPromotionRequest.h"
#include "AutoGen/SubSystems/Social/GetMyRequest.h"
#include "AutoGen/SubSystems/Social/PostFriendsInviteRequest.h"
#include "AutoGen/SubSystems/Social/DeleteFriendsInviteRequest.h"
#include "AutoGen/SubSystems/Social/DeleteFriendsRequest.h"
#include "AutoGen/SubSystems/Social/PostFriendsImportRequest.h"
#include "AutoGen/SubSystems/Social/PostFriendsMakeRequest.h"
#include "AutoGen/SubSystems/Social/GetSocialRequest.h"
#include "AutoGen/SubSystems/Social/PostBlockedRequest.h"
#include "AutoGen/SubSystems/Social/DeleteBlockedRequest.h"
#include "AutoGen/SubSystems/ChatV2/GetRoomsRequest.h"
#include "AutoGen/SubSystems/ChatV2/PostRoomsRequest.h"
#include "AutoGen/SubSystems/ChatV2/DeleteRoomsRequest.h"
#include "AutoGen/SubSystems/ChatV2/GetChatV2Request.h"
#include "AutoGen/SubSystems/ChatV2/PostMessagesRequest.h"
#include "AutoGen/SubSystems/Matchmaking/PutTickRequest.h"
#include "AutoGen/SubSystems/Matchmaking/GetMatchRequest.h"
#include "AutoGen/SubSystems/Matchmaking/PostMatchRequest.h"
#include "AutoGen/SubSystems/Matchmaking/DeleteMatchRequest.h"
#include "AutoGen/SubSystems/Commerce/GetSkusRequest.h"
#include "AutoGen/SubSystems/Commerce/GetCouponsCountRequest.h"
#include "AutoGen/SubSystems/Commerce/PostCatalogLegacyRequest.h"
#include "AutoGen/SubSystems/Commerce/GetCatalogRequest.h"
#include "AutoGen/SubSystems/Commerce/PostSkusRequest.h"
#include "AutoGen/SubSystems/Commerce/GetCommerceRequest.h"
#include "AutoGen/SubSystems/Commerce/PutListingsCooldownRequest.h"
#include "AutoGen/SubSystems/Commerce/GetOffersAdminRequest.h"
#include "AutoGen/SubSystems/Commerce/PostPurchaseRequest.h"
#include "AutoGen/SubSystems/Commerce/PutPurchaseRequest.h"
#include "AutoGen/SubSystems/Commerce/GetListingsRequest.h"
#include "AutoGen/SubSystems/Commerce/DeleteStatusRequest.h"
#include "AutoGen/SubSystems/Commerce/PostCouponsRequest.h"
#include "AutoGen/SubSystems/Commerce/PostStatsUpdateRequest.h"
#include "AutoGen/SubSystems/Commerce/GetOffersRequest.h"
#include "AutoGen/SubSystems/Calendars/ObjectCalendarsPostClaimRequest.h"
#include "AutoGen/SubSystems/Calendars/GetCalendarsRequest.h"
#include "AutoGen/SubSystems/Announcements/GetListTagsRequest.h"
#include "AutoGen/SubSystems/Announcements/BasicAnnouncementsGetListRequest.h"
#include "AutoGen/SubSystems/Announcements/BasicAnnouncementsGetSearchRequest.h"
#include "AutoGen/SubSystems/Announcements/GetListDefinitionsRequest.h"
#include "AutoGen/SubSystems/Announcements/PostAnnouncementsRequest.h"
#include "AutoGen/SubSystems/Announcements/BasicAnnouncementsDeleteAnnouncementsRequest.h"
#include "AutoGen/SubSystems/Announcements/BasicAnnouncementsGetContentRequest.h"
#include "AutoGen/SubSystems/Announcements/PutReadRequest.h"
#include "AutoGen/SubSystems/Announcements/ObjectAnnouncementsPostClaimRequest.h"
#include "AutoGen/SubSystems/Announcements/GetRawRequest.h"
#include "AutoGen/SubSystems/Announcements/GetAnnouncementsRequest.h"
#include "AutoGen/SubSystems/Announcements/ObjectAnnouncementsDeleteAnnouncementsRequest.h"
#include "AutoGen/SubSystems/Mail/GetTemplateRequest.h"
#include "AutoGen/SubSystems/Mail/BasicMailGetMailRequest.h"
#include "AutoGen/SubSystems/Mail/GetDetailRequest.h"
#include "AutoGen/SubSystems/Mail/GetCategoriesRequest.h"
#include "AutoGen/SubSystems/Mail/ObjectMailPostSearchRequest.h"
#include "AutoGen/SubSystems/Mail/PutBulkRequest.h"
#include "AutoGen/SubSystems/Mail/PutAcceptManyRequest.h"
#include "AutoGen/SubSystems/Mail/ObjectMailGetMailRequest.h"
#include "AutoGen/SubSystems/Mail/ObjectMailPutMailRequest.h"
#include "AutoGen/SubSystems/Mail/PutAttachmentsRequest.h"
#include "AutoGen/SubSystems/Mail/BasicMailPutMailRequest.h"
#include "AutoGen/SubSystems/Mail/BasicMailPostBulkRequest.h"
#include "AutoGen/SubSystems/Mail/ObjectMailPostBulkRequest.h"
#include "AutoGen/SubSystems/Mail/PostMailRequest.h"

template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPostMetricsUrlRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPostMetricsUrlRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPostMetricsUrlRequest, UGetSignedUrlResponse>(
	const int64&, UPostMetricsUrlRequest*, FOnPostMetricsUrlSuccess, FOnPostMetricsUrlError, FOnPostMetricsUrlComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPostMetricsUrlRequest, UGetSignedUrlResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostMetricsUrlRequest*, FOnPostMetricsUrlSuccess, FOnPostMetricsUrlError, FOnPostMetricsUrlComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPostMetricsUrlRequest*, TBeamFullResponseHandler<UPostMetricsUrlRequest*, UGetSignedUrlResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostMetricsUrlRequest*,
                                                                                   TBeamFullResponseHandler<UPostMetricsUrlRequest*, UGetSignedUrlResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UGetStoragePerformanceRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UGetStoragePerformanceRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UGetStoragePerformanceRequest, UPerformanceResponse>(
	const int64&, UGetStoragePerformanceRequest*, FOnGetStoragePerformanceSuccess, FOnGetStoragePerformanceError, FOnGetStoragePerformanceComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UGetStoragePerformanceRequest, UPerformanceResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetStoragePerformanceRequest*, FOnGetStoragePerformanceSuccess, FOnGetStoragePerformanceError, FOnGetStoragePerformanceComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UGetStoragePerformanceRequest*, TBeamFullResponseHandler<UGetStoragePerformanceRequest*, UPerformanceResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetStoragePerformanceRequest*,
                                                                                   TBeamFullResponseHandler<UGetStoragePerformanceRequest*, UPerformanceResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UGetManifestsRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UGetManifestsRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UGetManifestsRequest, UGetManifestsResponse>(
	const int64&, UGetManifestsRequest*, FOnGetManifestsSuccess, FOnGetManifestsError, FOnGetManifestsComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UGetManifestsRequest, UGetManifestsResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetManifestsRequest*, FOnGetManifestsSuccess, FOnGetManifestsError, FOnGetManifestsComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UGetManifestsRequest*, TBeamFullResponseHandler<UGetManifestsRequest*, UGetManifestsResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetManifestsRequest*,
                                                                                   TBeamFullResponseHandler<UGetManifestsRequest*, UGetManifestsResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UGetTemplatesRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UGetTemplatesRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UGetTemplatesRequest, UGetTemplatesResponse>(
	const int64&, UGetTemplatesRequest*, FOnGetTemplatesSuccess, FOnGetTemplatesError, FOnGetTemplatesComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UGetTemplatesRequest, UGetTemplatesResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetTemplatesRequest*, FOnGetTemplatesSuccess, FOnGetTemplatesError, FOnGetTemplatesComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UGetTemplatesRequest*, TBeamFullResponseHandler<UGetTemplatesRequest*, UGetTemplatesResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetTemplatesRequest*,
                                                                                   TBeamFullResponseHandler<UGetTemplatesRequest*, UGetTemplatesResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPostLogsUrlRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPostLogsUrlRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPostLogsUrlRequest, UGetSignedUrlResponse>(
	const int64&, UPostLogsUrlRequest*, FOnPostLogsUrlSuccess, FOnPostLogsUrlError, FOnPostLogsUrlComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPostLogsUrlRequest, UGetSignedUrlResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostLogsUrlRequest*, FOnPostLogsUrlSuccess, FOnPostLogsUrlError, FOnPostLogsUrlComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPostLogsUrlRequest*, TBeamFullResponseHandler<UPostLogsUrlRequest*, UGetSignedUrlResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostLogsUrlRequest*,
                                                                                   TBeamFullResponseHandler<UPostLogsUrlRequest*, UGetSignedUrlResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UGetUploadAPIRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UGetUploadAPIRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UGetUploadAPIRequest, UGetLambdaURI>(
	const int64&, UGetUploadAPIRequest*, FOnGetUploadAPISuccess, FOnGetUploadAPIError, FOnGetUploadAPIComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UGetUploadAPIRequest, UGetLambdaURI>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetUploadAPIRequest*, FOnGetUploadAPISuccess, FOnGetUploadAPIError, FOnGetUploadAPIComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UGetUploadAPIRequest*, TBeamFullResponseHandler<UGetUploadAPIRequest*, UGetLambdaURI*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetUploadAPIRequest*,
                                                                                   TBeamFullResponseHandler<UGetUploadAPIRequest*, UGetLambdaURI*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UGetStatusRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UGetStatusRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UGetStatusRequest, UGetStatusResponse>(
	const int64&, UGetStatusRequest*, FOnGetStatusSuccess, FOnGetStatusError, FOnGetStatusComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UGetStatusRequest, UGetStatusResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetStatusRequest*, FOnGetStatusSuccess, FOnGetStatusError, FOnGetStatusComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UGetStatusRequest*, TBeamFullResponseHandler<UGetStatusRequest*, UGetStatusResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetStatusRequest*,
                                                                                   TBeamFullResponseHandler<UGetStatusRequest*, UGetStatusResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UGetManifestCurrentRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UGetManifestCurrentRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UGetManifestCurrentRequest, UGetCurrentManifestResponse>(
	const int64&, UGetManifestCurrentRequest*, FOnGetManifestCurrentSuccess, FOnGetManifestCurrentError, FOnGetManifestCurrentComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UGetManifestCurrentRequest, UGetCurrentManifestResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetManifestCurrentRequest*, FOnGetManifestCurrentSuccess, FOnGetManifestCurrentError, FOnGetManifestCurrentComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UGetManifestCurrentRequest*, TBeamFullResponseHandler<UGetManifestCurrentRequest*, UGetCurrentManifestResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetManifestCurrentRequest*,
                                                                                   TBeamFullResponseHandler<UGetManifestCurrentRequest*, UGetCurrentManifestResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPostManifestPullRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPostManifestPullRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPostManifestPullRequest, UManifestChecksums>(
	const int64&, UPostManifestPullRequest*, FOnPostManifestPullSuccess, FOnPostManifestPullError, FOnPostManifestPullComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPostManifestPullRequest, UManifestChecksums>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostManifestPullRequest*, FOnPostManifestPullSuccess, FOnPostManifestPullError, FOnPostManifestPullComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPostManifestPullRequest*, TBeamFullResponseHandler<UPostManifestPullRequest*, UManifestChecksums*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostManifestPullRequest*,
                                                                                   TBeamFullResponseHandler<UPostManifestPullRequest*, UManifestChecksums*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UGetRegistryRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UGetRegistryRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UGetRegistryRequest, UGetElasticContainerRegistryURI>(
	const int64&, UGetRegistryRequest*, FOnGetRegistrySuccess, FOnGetRegistryError, FOnGetRegistryComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UGetRegistryRequest, UGetElasticContainerRegistryURI>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetRegistryRequest*, FOnGetRegistrySuccess, FOnGetRegistryError, FOnGetRegistryComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UGetRegistryRequest*, TBeamFullResponseHandler<UGetRegistryRequest*, UGetElasticContainerRegistryURI*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetRegistryRequest*,
                                                                                   TBeamFullResponseHandler<UGetRegistryRequest*, UGetElasticContainerRegistryURI*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPostManifestDeployRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPostManifestDeployRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPostManifestDeployRequest, UEmptyResponse>(
	const int64&, UPostManifestDeployRequest*, FOnPostManifestDeploySuccess, FOnPostManifestDeployError, FOnPostManifestDeployComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPostManifestDeployRequest, UEmptyResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostManifestDeployRequest*, FOnPostManifestDeploySuccess, FOnPostManifestDeployError, FOnPostManifestDeployComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPostManifestDeployRequest*, TBeamFullResponseHandler<UPostManifestDeployRequest*, UEmptyResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostManifestDeployRequest*,
                                                                                   TBeamFullResponseHandler<UPostManifestDeployRequest*, UEmptyResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UGetStorageConnectionRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UGetStorageConnectionRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UGetStorageConnectionRequest, UConnectionString>(
	const int64&, UGetStorageConnectionRequest*, FOnGetStorageConnectionSuccess, FOnGetStorageConnectionError, FOnGetStorageConnectionComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UGetStorageConnectionRequest, UConnectionString>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetStorageConnectionRequest*, FOnGetStorageConnectionSuccess, FOnGetStorageConnectionError, FOnGetStorageConnectionComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UGetStorageConnectionRequest*, TBeamFullResponseHandler<UGetStorageConnectionRequest*, UConnectionString*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetStorageConnectionRequest*,
                                                                                   TBeamFullResponseHandler<UGetStorageConnectionRequest*, UConnectionString*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UGetManifestRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UGetManifestRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UGetManifestRequest, UGetManifestResponse>(
	const int64&, UGetManifestRequest*, FOnGetManifestSuccess, FOnGetManifestError, FOnGetManifestComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UGetManifestRequest, UGetManifestResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetManifestRequest*, FOnGetManifestSuccess, FOnGetManifestError, FOnGetManifestComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UGetManifestRequest*, TBeamFullResponseHandler<UGetManifestRequest*, UGetManifestResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetManifestRequest*,
                                                                                   TBeamFullResponseHandler<UGetManifestRequest*, UGetManifestResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPostManifestRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPostManifestRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPostManifestRequest, UPostManifestResponse>(
	const int64&, UPostManifestRequest*, FOnPostManifestSuccess, FOnPostManifestError, FOnPostManifestComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPostManifestRequest, UPostManifestResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostManifestRequest*, FOnPostManifestSuccess, FOnPostManifestError, FOnPostManifestComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPostManifestRequest*, TBeamFullResponseHandler<UPostManifestRequest*, UPostManifestResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostManifestRequest*,
                                                                                   TBeamFullResponseHandler<UPostManifestRequest*, UPostManifestResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UGetEventPlayersRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UGetEventPlayersRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UGetEventPlayersRequest, UEventPlayerView>(
	const int64&, UGetEventPlayersRequest*, FOnGetEventPlayersSuccess, FOnGetEventPlayersError, FOnGetEventPlayersComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UGetEventPlayersRequest, UEventPlayerView>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetEventPlayersRequest*, FOnGetEventPlayersSuccess, FOnGetEventPlayersError, FOnGetEventPlayersComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UGetEventPlayersRequest*, TBeamFullResponseHandler<UGetEventPlayersRequest*, UEventPlayerView*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetEventPlayersRequest*,
                                                                                   TBeamFullResponseHandler<UGetEventPlayersRequest*, UEventPlayerView*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UObjectEventPlayersPostClaimRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UObjectEventPlayersPostClaimRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UObjectEventPlayersPostClaimRequest, UEventClaimResponse>(
	const int64&, UObjectEventPlayersPostClaimRequest*, FOnObjectEventPlayersPostClaimSuccess, FOnObjectEventPlayersPostClaimError, FOnObjectEventPlayersPostClaimComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UObjectEventPlayersPostClaimRequest, UEventClaimResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UObjectEventPlayersPostClaimRequest*, FOnObjectEventPlayersPostClaimSuccess, FOnObjectEventPlayersPostClaimError, FOnObjectEventPlayersPostClaimComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UObjectEventPlayersPostClaimRequest*, TBeamFullResponseHandler<UObjectEventPlayersPostClaimRequest*, UEventClaimResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UObjectEventPlayersPostClaimRequest*,
                                                                                   TBeamFullResponseHandler<UObjectEventPlayersPostClaimRequest*, UEventClaimResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPutScoreRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPutScoreRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPutScoreRequest, UCommonResponse>(
	const int64&, UPutScoreRequest*, FOnPutScoreSuccess, FOnPutScoreError, FOnPutScoreComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPutScoreRequest, UCommonResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPutScoreRequest*, FOnPutScoreSuccess, FOnPutScoreError, FOnPutScoreComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPutScoreRequest*, TBeamFullResponseHandler<UPutScoreRequest*, UCommonResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPutScoreRequest*,
                                                                                   TBeamFullResponseHandler<UPutScoreRequest*, UCommonResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UGetRunningRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UGetRunningRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UGetRunningRequest, UEventQueryResponse>(
	const int64&, UGetRunningRequest*, FOnGetRunningSuccess, FOnGetRunningError, FOnGetRunningComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UGetRunningRequest, UEventQueryResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetRunningRequest*, FOnGetRunningSuccess, FOnGetRunningError, FOnGetRunningComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UGetRunningRequest*, TBeamFullResponseHandler<UGetRunningRequest*, UEventQueryResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetRunningRequest*,
                                                                                   TBeamFullResponseHandler<UGetRunningRequest*, UEventQueryResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UBasicEventsGetContentRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UBasicEventsGetContentRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UBasicEventsGetContentRequest, UEventContentResponse>(
	const int64&, UBasicEventsGetContentRequest*, FOnBasicEventsGetContentSuccess, FOnBasicEventsGetContentError, FOnBasicEventsGetContentComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UBasicEventsGetContentRequest, UEventContentResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UBasicEventsGetContentRequest*, FOnBasicEventsGetContentSuccess, FOnBasicEventsGetContentError, FOnBasicEventsGetContentComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UBasicEventsGetContentRequest*, TBeamFullResponseHandler<UBasicEventsGetContentRequest*, UEventContentResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UBasicEventsGetContentRequest*,
                                                                                   TBeamFullResponseHandler<UBasicEventsGetContentRequest*, UEventContentResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UGetCalendarRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UGetCalendarRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UGetCalendarRequest, UEventsInDateRangeResponse>(
	const int64&, UGetCalendarRequest*, FOnGetCalendarSuccess, FOnGetCalendarError, FOnGetCalendarComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UGetCalendarRequest, UEventsInDateRangeResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetCalendarRequest*, FOnGetCalendarSuccess, FOnGetCalendarError, FOnGetCalendarComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UGetCalendarRequest*, TBeamFullResponseHandler<UGetCalendarRequest*, UEventsInDateRangeResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetCalendarRequest*,
                                                                                   TBeamFullResponseHandler<UGetCalendarRequest*, UEventsInDateRangeResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPostApplyContentRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPostApplyContentRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPostApplyContentRequest, UCommonResponse>(
	const int64&, UPostApplyContentRequest*, FOnPostApplyContentSuccess, FOnPostApplyContentError, FOnPostApplyContentComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPostApplyContentRequest, UCommonResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostApplyContentRequest*, FOnPostApplyContentSuccess, FOnPostApplyContentError, FOnPostApplyContentComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPostApplyContentRequest*, TBeamFullResponseHandler<UPostApplyContentRequest*, UCommonResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostApplyContentRequest*,
                                                                                   TBeamFullResponseHandler<UPostApplyContentRequest*, UCommonResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPutEndPhaseRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPutEndPhaseRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPutEndPhaseRequest, UCommonResponse>(
	const int64&, UPutEndPhaseRequest*, FOnPutEndPhaseSuccess, FOnPutEndPhaseError, FOnPutEndPhaseComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPutEndPhaseRequest, UCommonResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPutEndPhaseRequest*, FOnPutEndPhaseSuccess, FOnPutEndPhaseError, FOnPutEndPhaseComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPutEndPhaseRequest*, TBeamFullResponseHandler<UPutEndPhaseRequest*, UCommonResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPutEndPhaseRequest*,
                                                                                   TBeamFullResponseHandler<UPutEndPhaseRequest*, UCommonResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UGetEventsRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UGetEventsRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UGetEventsRequest, UEventObjectData>(
	const int64&, UGetEventsRequest*, FOnGetEventsSuccess, FOnGetEventsError, FOnGetEventsComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UGetEventsRequest, UEventObjectData>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetEventsRequest*, FOnGetEventsSuccess, FOnGetEventsError, FOnGetEventsComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UGetEventsRequest*, TBeamFullResponseHandler<UGetEventsRequest*, UEventObjectData*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetEventsRequest*,
                                                                                   TBeamFullResponseHandler<UGetEventsRequest*, UEventObjectData*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UGetPingRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UGetPingRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UGetPingRequest, UPingRsp>(
	const int64&, UGetPingRequest*, FOnGetPingSuccess, FOnGetPingError, FOnGetPingComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UGetPingRequest, UPingRsp>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetPingRequest*, FOnGetPingSuccess, FOnGetPingError, FOnGetPingComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UGetPingRequest*, TBeamFullResponseHandler<UGetPingRequest*, UPingRsp*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetPingRequest*,
                                                                                   TBeamFullResponseHandler<UGetPingRequest*, UPingRsp*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPutContentRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPutContentRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPutContentRequest, UCommonResponse>(
	const int64&, UPutContentRequest*, FOnPutContentSuccess, FOnPutContentError, FOnPutContentComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPutContentRequest, UCommonResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPutContentRequest*, FOnPutContentSuccess, FOnPutContentError, FOnPutContentComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPutContentRequest*, TBeamFullResponseHandler<UPutContentRequest*, UCommonResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPutContentRequest*,
                                                                                   TBeamFullResponseHandler<UPutContentRequest*, UCommonResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UDeleteContentRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UDeleteContentRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UDeleteContentRequest, UCommonResponse>(
	const int64&, UDeleteContentRequest*, FOnDeleteContentSuccess, FOnDeleteContentError, FOnDeleteContentComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UDeleteContentRequest, UCommonResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UDeleteContentRequest*, FOnDeleteContentSuccess, FOnDeleteContentError, FOnDeleteContentComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UDeleteContentRequest*, TBeamFullResponseHandler<UDeleteContentRequest*, UCommonResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UDeleteContentRequest*,
                                                                                   TBeamFullResponseHandler<UDeleteContentRequest*, UCommonResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPutRefreshRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPutRefreshRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPutRefreshRequest, UCommonResponse>(
	const int64&, UPutRefreshRequest*, FOnPutRefreshSuccess, FOnPutRefreshError, FOnPutRefreshComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPutRefreshRequest, UCommonResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPutRefreshRequest*, FOnPutRefreshSuccess, FOnPutRefreshError, FOnPutRefreshComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPutRefreshRequest*, TBeamFullResponseHandler<UPutRefreshRequest*, UCommonResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPutRefreshRequest*,
                                                                                   TBeamFullResponseHandler<UPutRefreshRequest*, UCommonResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UGetAvailabilityRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UGetAvailabilityRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UGetAvailabilityRequest, UAvailabilityResponse>(
	const int64&, UGetAvailabilityRequest*, FOnGetAvailabilitySuccess, FOnGetAvailabilityError, FOnGetAvailabilityComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UGetAvailabilityRequest, UAvailabilityResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetAvailabilityRequest*, FOnGetAvailabilitySuccess, FOnGetAvailabilityError, FOnGetAvailabilityComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UGetAvailabilityRequest*, TBeamFullResponseHandler<UGetAvailabilityRequest*, UAvailabilityResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetAvailabilityRequest*,
                                                                                   TBeamFullResponseHandler<UGetAvailabilityRequest*, UAvailabilityResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UGetRecommendedRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UGetRecommendedRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UGetRecommendedRequest, UGroupSearchResponse>(
	const int64&, UGetRecommendedRequest*, FOnGetRecommendedSuccess, FOnGetRecommendedError, FOnGetRecommendedComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UGetRecommendedRequest, UGroupSearchResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetRecommendedRequest*, FOnGetRecommendedSuccess, FOnGetRecommendedError, FOnGetRecommendedComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UGetRecommendedRequest*, TBeamFullResponseHandler<UGetRecommendedRequest*, UGroupSearchResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetRecommendedRequest*,
                                                                                   TBeamFullResponseHandler<UGetRecommendedRequest*, UGroupSearchResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPostJoinRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPostJoinRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPostJoinRequest, UGroupMembershipResponse>(
	const int64&, UPostJoinRequest*, FOnPostJoinSuccess, FOnPostJoinError, FOnPostJoinComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPostJoinRequest, UGroupMembershipResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostJoinRequest*, FOnPostJoinSuccess, FOnPostJoinError, FOnPostJoinComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPostJoinRequest*, TBeamFullResponseHandler<UPostJoinRequest*, UGroupMembershipResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostJoinRequest*,
                                                                                   TBeamFullResponseHandler<UPostJoinRequest*, UGroupMembershipResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UDeleteJoinRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UDeleteJoinRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UDeleteJoinRequest, UGroupMembershipResponse>(
	const int64&, UDeleteJoinRequest*, FOnDeleteJoinSuccess, FOnDeleteJoinError, FOnDeleteJoinComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UDeleteJoinRequest, UGroupMembershipResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UDeleteJoinRequest*, FOnDeleteJoinSuccess, FOnDeleteJoinError, FOnDeleteJoinComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UDeleteJoinRequest*, TBeamFullResponseHandler<UDeleteJoinRequest*, UGroupMembershipResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UDeleteJoinRequest*,
                                                                                   TBeamFullResponseHandler<UDeleteJoinRequest*, UGroupMembershipResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPostGroupRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPostGroupRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPostGroupRequest, UGroupCreateResponse>(
	const int64&, UPostGroupRequest*, FOnPostGroupSuccess, FOnPostGroupError, FOnPostGroupComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPostGroupRequest, UGroupCreateResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostGroupRequest*, FOnPostGroupSuccess, FOnPostGroupError, FOnPostGroupComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPostGroupRequest*, TBeamFullResponseHandler<UPostGroupRequest*, UGroupCreateResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostGroupRequest*,
                                                                                   TBeamFullResponseHandler<UPostGroupRequest*, UGroupCreateResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UObjectGroupUsersGetSearchRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UObjectGroupUsersGetSearchRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UObjectGroupUsersGetSearchRequest, UGroupSearchResponse>(
	const int64&, UObjectGroupUsersGetSearchRequest*, FOnObjectGroupUsersGetSearchSuccess, FOnObjectGroupUsersGetSearchError, FOnObjectGroupUsersGetSearchComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UObjectGroupUsersGetSearchRequest, UGroupSearchResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UObjectGroupUsersGetSearchRequest*, FOnObjectGroupUsersGetSearchSuccess, FOnObjectGroupUsersGetSearchError, FOnObjectGroupUsersGetSearchComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UObjectGroupUsersGetSearchRequest*, TBeamFullResponseHandler<UObjectGroupUsersGetSearchRequest*, UGroupSearchResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UObjectGroupUsersGetSearchRequest*,
                                                                                   TBeamFullResponseHandler<UObjectGroupUsersGetSearchRequest*, UGroupSearchResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UGetGroupUsersRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UGetGroupUsersRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UGetGroupUsersRequest, UGroupUser>(
	const int64&, UGetGroupUsersRequest*, FOnGetGroupUsersSuccess, FOnGetGroupUsersError, FOnGetGroupUsersComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UGetGroupUsersRequest, UGroupUser>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetGroupUsersRequest*, FOnGetGroupUsersSuccess, FOnGetGroupUsersError, FOnGetGroupUsersComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UGetGroupUsersRequest*, TBeamFullResponseHandler<UGetGroupUsersRequest*, UGroupUser*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetGroupUsersRequest*,
                                                                                   TBeamFullResponseHandler<UGetGroupUsersRequest*, UGroupUser*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPostKickRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPostKickRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPostKickRequest, UGroupMembershipResponse>(
	const int64&, UPostKickRequest*, FOnPostKickSuccess, FOnPostKickError, FOnPostKickComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPostKickRequest, UGroupMembershipResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostKickRequest*, FOnPostKickSuccess, FOnPostKickError, FOnPostKickComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPostKickRequest*, TBeamFullResponseHandler<UPostKickRequest*, UGroupMembershipResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostKickRequest*,
                                                                                   TBeamFullResponseHandler<UPostKickRequest*, UGroupMembershipResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UDeleteMemberRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UDeleteMemberRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UDeleteMemberRequest, UGroupMembershipResponse>(
	const int64&, UDeleteMemberRequest*, FOnDeleteMemberSuccess, FOnDeleteMemberError, FOnDeleteMemberComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UDeleteMemberRequest, UGroupMembershipResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UDeleteMemberRequest*, FOnDeleteMemberSuccess, FOnDeleteMemberError, FOnDeleteMemberComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UDeleteMemberRequest*, TBeamFullResponseHandler<UDeleteMemberRequest*, UGroupMembershipResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UDeleteMemberRequest*,
                                                                                   TBeamFullResponseHandler<UDeleteMemberRequest*, UGroupMembershipResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UObjectGroupsGetGroupsRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UObjectGroupsGetGroupsRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UObjectGroupsGetGroupsRequest, UGroup>(
	const int64&, UObjectGroupsGetGroupsRequest*, FOnObjectGroupsGetGroupsSuccess, FOnObjectGroupsGetGroupsError, FOnObjectGroupsGetGroupsComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UObjectGroupsGetGroupsRequest, UGroup>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UObjectGroupsGetGroupsRequest*, FOnObjectGroupsGetGroupsSuccess, FOnObjectGroupsGetGroupsError, FOnObjectGroupsGetGroupsComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UObjectGroupsGetGroupsRequest*, TBeamFullResponseHandler<UObjectGroupsGetGroupsRequest*, UGroup*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UObjectGroupsGetGroupsRequest*,
                                                                                   TBeamFullResponseHandler<UObjectGroupsGetGroupsRequest*, UGroup*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPutGroupsRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPutGroupsRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPutGroupsRequest, UCommonResponse>(
	const int64&, UPutGroupsRequest*, FOnPutGroupsSuccess, FOnPutGroupsError, FOnPutGroupsComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPutGroupsRequest, UCommonResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPutGroupsRequest*, FOnPutGroupsSuccess, FOnPutGroupsError, FOnPutGroupsComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPutGroupsRequest*, TBeamFullResponseHandler<UPutGroupsRequest*, UCommonResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPutGroupsRequest*,
                                                                                   TBeamFullResponseHandler<UPutGroupsRequest*, UCommonResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UDeleteGroupsRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UDeleteGroupsRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UDeleteGroupsRequest, UCommonResponse>(
	const int64&, UDeleteGroupsRequest*, FOnDeleteGroupsSuccess, FOnDeleteGroupsError, FOnDeleteGroupsComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UDeleteGroupsRequest, UCommonResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UDeleteGroupsRequest*, FOnDeleteGroupsSuccess, FOnDeleteGroupsError, FOnDeleteGroupsComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UDeleteGroupsRequest*, TBeamFullResponseHandler<UDeleteGroupsRequest*, UCommonResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UDeleteGroupsRequest*,
                                                                                   TBeamFullResponseHandler<UDeleteGroupsRequest*, UCommonResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UObjectGroupsPutRoleRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UObjectGroupsPutRoleRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UObjectGroupsPutRoleRequest, UCommonResponse>(
	const int64&, UObjectGroupsPutRoleRequest*, FOnObjectGroupsPutRoleSuccess, FOnObjectGroupsPutRoleError, FOnObjectGroupsPutRoleComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UObjectGroupsPutRoleRequest, UCommonResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UObjectGroupsPutRoleRequest*, FOnObjectGroupsPutRoleSuccess, FOnObjectGroupsPutRoleError, FOnObjectGroupsPutRoleComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UObjectGroupsPutRoleRequest*, TBeamFullResponseHandler<UObjectGroupsPutRoleRequest*, UCommonResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UObjectGroupsPutRoleRequest*,
                                                                                   TBeamFullResponseHandler<UObjectGroupsPutRoleRequest*, UCommonResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPostApplyRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPostApplyRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPostApplyRequest, UCommonResponse>(
	const int64&, UPostApplyRequest*, FOnPostApplySuccess, FOnPostApplyError, FOnPostApplyComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPostApplyRequest, UCommonResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostApplyRequest*, FOnPostApplySuccess, FOnPostApplyError, FOnPostApplyComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPostApplyRequest*, TBeamFullResponseHandler<UPostApplyRequest*, UCommonResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostApplyRequest*,
                                                                                   TBeamFullResponseHandler<UPostApplyRequest*, UCommonResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPostDonationsRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPostDonationsRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPostDonationsRequest, UEmptyResponse>(
	const int64&, UPostDonationsRequest*, FOnPostDonationsSuccess, FOnPostDonationsError, FOnPostDonationsComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPostDonationsRequest, UEmptyResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostDonationsRequest*, FOnPostDonationsSuccess, FOnPostDonationsError, FOnPostDonationsComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPostDonationsRequest*, TBeamFullResponseHandler<UPostDonationsRequest*, UEmptyResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostDonationsRequest*,
                                                                                   TBeamFullResponseHandler<UPostDonationsRequest*, UEmptyResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPutDonationsRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPutDonationsRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPutDonationsRequest, UEmptyResponse>(
	const int64&, UPutDonationsRequest*, FOnPutDonationsSuccess, FOnPutDonationsError, FOnPutDonationsComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPutDonationsRequest, UEmptyResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPutDonationsRequest*, FOnPutDonationsSuccess, FOnPutDonationsError, FOnPutDonationsComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPutDonationsRequest*, TBeamFullResponseHandler<UPutDonationsRequest*, UEmptyResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPutDonationsRequest*,
                                                                                   TBeamFullResponseHandler<UPutDonationsRequest*, UEmptyResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPutDonationsClaimRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPutDonationsClaimRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPutDonationsClaimRequest, UEmptyResponse>(
	const int64&, UPutDonationsClaimRequest*, FOnPutDonationsClaimSuccess, FOnPutDonationsClaimError, FOnPutDonationsClaimComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPutDonationsClaimRequest, UEmptyResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPutDonationsClaimRequest*, FOnPutDonationsClaimSuccess, FOnPutDonationsClaimError, FOnPutDonationsClaimComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPutDonationsClaimRequest*, TBeamFullResponseHandler<UPutDonationsClaimRequest*, UEmptyResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPutDonationsClaimRequest*,
                                                                                   TBeamFullResponseHandler<UPutDonationsClaimRequest*, UEmptyResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPostInviteRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPostInviteRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPostInviteRequest, UCommonResponse>(
	const int64&, UPostInviteRequest*, FOnPostInviteSuccess, FOnPostInviteError, FOnPostInviteComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPostInviteRequest, UCommonResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostInviteRequest*, FOnPostInviteSuccess, FOnPostInviteError, FOnPostInviteComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPostInviteRequest*, TBeamFullResponseHandler<UPostInviteRequest*, UCommonResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostInviteRequest*,
                                                                                   TBeamFullResponseHandler<UPostInviteRequest*, UCommonResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPostPetitionRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPostPetitionRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPostPetitionRequest, UCommonResponse>(
	const int64&, UPostPetitionRequest*, FOnPostPetitionSuccess, FOnPostPetitionError, FOnPostPetitionComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPostPetitionRequest, UCommonResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostPetitionRequest*, FOnPostPetitionSuccess, FOnPostPetitionError, FOnPostPetitionComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPostPetitionRequest*, TBeamFullResponseHandler<UPostPetitionRequest*, UCommonResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostPetitionRequest*,
                                                                                   TBeamFullResponseHandler<UPostPetitionRequest*, UCommonResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UGetItemsRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UGetItemsRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UGetItemsRequest, UItemContentResponse>(
	const int64&, UGetItemsRequest*, FOnGetItemsSuccess, FOnGetItemsError, FOnGetItemsComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UGetItemsRequest, UItemContentResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetItemsRequest*, FOnGetItemsSuccess, FOnGetItemsError, FOnGetItemsComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UGetItemsRequest*, TBeamFullResponseHandler<UGetItemsRequest*, UItemContentResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetItemsRequest*,
                                                                                   TBeamFullResponseHandler<UGetItemsRequest*, UItemContentResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UGetCurrencyRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UGetCurrencyRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UGetCurrencyRequest, UCurrencyContentResponse>(
	const int64&, UGetCurrencyRequest*, FOnGetCurrencySuccess, FOnGetCurrencyError, FOnGetCurrencyComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UGetCurrencyRequest, UCurrencyContentResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetCurrencyRequest*, FOnGetCurrencySuccess, FOnGetCurrencyError, FOnGetCurrencyComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UGetCurrencyRequest*, TBeamFullResponseHandler<UGetCurrencyRequest*, UCurrencyContentResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetCurrencyRequest*,
                                                                                   TBeamFullResponseHandler<UGetCurrencyRequest*, UCurrencyContentResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPutPreviewRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPutPreviewRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPutPreviewRequest, UPreviewVipBonusResponse>(
	const int64&, UPutPreviewRequest*, FOnPutPreviewSuccess, FOnPutPreviewError, FOnPutPreviewComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPutPreviewRequest, UPreviewVipBonusResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPutPreviewRequest*, FOnPutPreviewSuccess, FOnPutPreviewError, FOnPutPreviewComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPutPreviewRequest*, TBeamFullResponseHandler<UPutPreviewRequest*, UPreviewVipBonusResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPutPreviewRequest*,
                                                                                   TBeamFullResponseHandler<UPutPreviewRequest*, UPreviewVipBonusResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UGetMultipliersRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UGetMultipliersRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UGetMultipliersRequest, UMultipliersGetResponse>(
	const int64&, UGetMultipliersRequest*, FOnGetMultipliersSuccess, FOnGetMultipliersError, FOnGetMultipliersComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UGetMultipliersRequest, UMultipliersGetResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetMultipliersRequest*, FOnGetMultipliersSuccess, FOnGetMultipliersError, FOnGetMultipliersComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UGetMultipliersRequest*, TBeamFullResponseHandler<UGetMultipliersRequest*, UMultipliersGetResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetMultipliersRequest*,
                                                                                   TBeamFullResponseHandler<UGetMultipliersRequest*, UMultipliersGetResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UGetInventoryRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UGetInventoryRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UGetInventoryRequest, UInventoryView>(
	const int64&, UGetInventoryRequest*, FOnGetInventorySuccess, FOnGetInventoryError, FOnGetInventoryComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UGetInventoryRequest, UInventoryView>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetInventoryRequest*, FOnGetInventorySuccess, FOnGetInventoryError, FOnGetInventoryComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UGetInventoryRequest*, TBeamFullResponseHandler<UGetInventoryRequest*, UInventoryView*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetInventoryRequest*,
                                                                                   TBeamFullResponseHandler<UGetInventoryRequest*, UInventoryView*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPostInventoryRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPostInventoryRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPostInventoryRequest, UInventoryView>(
	const int64&, UPostInventoryRequest*, FOnPostInventorySuccess, FOnPostInventoryError, FOnPostInventoryComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPostInventoryRequest, UInventoryView>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostInventoryRequest*, FOnPostInventorySuccess, FOnPostInventoryError, FOnPostInventoryComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPostInventoryRequest*, TBeamFullResponseHandler<UPostInventoryRequest*, UInventoryView*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostInventoryRequest*,
                                                                                   TBeamFullResponseHandler<UPostInventoryRequest*, UInventoryView*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPutInventoryRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPutInventoryRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPutInventoryRequest, UCommonResponse>(
	const int64&, UPutInventoryRequest*, FOnPutInventorySuccess, FOnPutInventoryError, FOnPutInventoryComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPutInventoryRequest, UCommonResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPutInventoryRequest*, FOnPutInventorySuccess, FOnPutInventoryError, FOnPutInventoryComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPutInventoryRequest*, TBeamFullResponseHandler<UPutInventoryRequest*, UCommonResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPutInventoryRequest*,
                                                                                   TBeamFullResponseHandler<UPutInventoryRequest*, UCommonResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UDeleteTransactionRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UDeleteTransactionRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UDeleteTransactionRequest, UCommonResponse>(
	const int64&, UDeleteTransactionRequest*, FOnDeleteTransactionSuccess, FOnDeleteTransactionError, FOnDeleteTransactionComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UDeleteTransactionRequest, UCommonResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UDeleteTransactionRequest*, FOnDeleteTransactionSuccess, FOnDeleteTransactionError, FOnDeleteTransactionComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UDeleteTransactionRequest*, TBeamFullResponseHandler<UDeleteTransactionRequest*, UCommonResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UDeleteTransactionRequest*,
                                                                                   TBeamFullResponseHandler<UDeleteTransactionRequest*, UCommonResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPutTransferRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPutTransferRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPutTransferRequest, UCommonResponse>(
	const int64&, UPutTransferRequest*, FOnPutTransferSuccess, FOnPutTransferError, FOnPutTransferComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPutTransferRequest, UCommonResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPutTransferRequest*, FOnPutTransferSuccess, FOnPutTransferError, FOnPutTransferComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPutTransferRequest*, TBeamFullResponseHandler<UPutTransferRequest*, UCommonResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPutTransferRequest*,
                                                                                   TBeamFullResponseHandler<UPutTransferRequest*, UCommonResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UGetRanksRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UGetRanksRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UGetRanksRequest, ULeaderBoardViewResponse>(
	const int64&, UGetRanksRequest*, FOnGetRanksSuccess, FOnGetRanksError, FOnGetRanksComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UGetRanksRequest, ULeaderBoardViewResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetRanksRequest*, FOnGetRanksSuccess, FOnGetRanksError, FOnGetRanksComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UGetRanksRequest*, TBeamFullResponseHandler<UGetRanksRequest*, ULeaderBoardViewResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetRanksRequest*,
                                                                                   TBeamFullResponseHandler<UGetRanksRequest*, ULeaderBoardViewResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UGetMatchesRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UGetMatchesRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UGetMatchesRequest, UMatchMakingMatchesPvpResponse>(
	const int64&, UGetMatchesRequest*, FOnGetMatchesSuccess, FOnGetMatchesError, FOnGetMatchesComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UGetMatchesRequest, UMatchMakingMatchesPvpResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetMatchesRequest*, FOnGetMatchesSuccess, FOnGetMatchesError, FOnGetMatchesComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UGetMatchesRequest*, TBeamFullResponseHandler<UGetMatchesRequest*, UMatchMakingMatchesPvpResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetMatchesRequest*,
                                                                                   TBeamFullResponseHandler<UGetMatchesRequest*, UMatchMakingMatchesPvpResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPutEntryRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPutEntryRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPutEntryRequest, UCommonResponse>(
	const int64&, UPutEntryRequest*, FOnPutEntrySuccess, FOnPutEntryError, FOnPutEntryComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPutEntryRequest, UCommonResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPutEntryRequest*, FOnPutEntrySuccess, FOnPutEntryError, FOnPutEntryComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPutEntryRequest*, TBeamFullResponseHandler<UPutEntryRequest*, UCommonResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPutEntryRequest*,
                                                                                   TBeamFullResponseHandler<UPutEntryRequest*, UCommonResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UGetViewRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UGetViewRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UGetViewRequest, ULeaderBoardViewResponse>(
	const int64&, UGetViewRequest*, FOnGetViewSuccess, FOnGetViewError, FOnGetViewComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UGetViewRequest, ULeaderBoardViewResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetViewRequest*, FOnGetViewSuccess, FOnGetViewError, FOnGetViewComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UGetViewRequest*, TBeamFullResponseHandler<UGetViewRequest*, ULeaderBoardViewResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetViewRequest*,
                                                                                   TBeamFullResponseHandler<UGetViewRequest*, ULeaderBoardViewResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UBasicLeaderboardsGetListRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UBasicLeaderboardsGetListRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UBasicLeaderboardsGetListRequest, ULeaderboardListResponse>(
	const int64&, UBasicLeaderboardsGetListRequest*, FOnBasicLeaderboardsGetListSuccess, FOnBasicLeaderboardsGetListError, FOnBasicLeaderboardsGetListComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UBasicLeaderboardsGetListRequest, ULeaderboardListResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UBasicLeaderboardsGetListRequest*, FOnBasicLeaderboardsGetListSuccess, FOnBasicLeaderboardsGetListError, FOnBasicLeaderboardsGetListComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UBasicLeaderboardsGetListRequest*, TBeamFullResponseHandler<UBasicLeaderboardsGetListRequest*, ULeaderboardListResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UBasicLeaderboardsGetListRequest*,
                                                                                   TBeamFullResponseHandler<UBasicLeaderboardsGetListRequest*, ULeaderboardListResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UGetPlayerRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UGetPlayerRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UGetPlayerRequest, UListLeaderBoardViewResponse>(
	const int64&, UGetPlayerRequest*, FOnGetPlayerSuccess, FOnGetPlayerError, FOnGetPlayerComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UGetPlayerRequest, UListLeaderBoardViewResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetPlayerRequest*, FOnGetPlayerSuccess, FOnGetPlayerError, FOnGetPlayerComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UGetPlayerRequest*, TBeamFullResponseHandler<UGetPlayerRequest*, UListLeaderBoardViewResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetPlayerRequest*,
                                                                                   TBeamFullResponseHandler<UGetPlayerRequest*, UListLeaderBoardViewResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UBasicLeaderboardsGetAssignmentRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UBasicLeaderboardsGetAssignmentRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UBasicLeaderboardsGetAssignmentRequest, ULeaderboardAssignmentInfo>(
	const int64&, UBasicLeaderboardsGetAssignmentRequest*, FOnBasicLeaderboardsGetAssignmentSuccess, FOnBasicLeaderboardsGetAssignmentError, FOnBasicLeaderboardsGetAssignmentComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UBasicLeaderboardsGetAssignmentRequest, ULeaderboardAssignmentInfo>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UBasicLeaderboardsGetAssignmentRequest*, FOnBasicLeaderboardsGetAssignmentSuccess, FOnBasicLeaderboardsGetAssignmentError, FOnBasicLeaderboardsGetAssignmentComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UBasicLeaderboardsGetAssignmentRequest*, TBeamFullResponseHandler<UBasicLeaderboardsGetAssignmentRequest*, ULeaderboardAssignmentInfo*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UBasicLeaderboardsGetAssignmentRequest*,
                                                                                   TBeamFullResponseHandler<UBasicLeaderboardsGetAssignmentRequest*, ULeaderboardAssignmentInfo*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UGetUidRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UGetUidRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UGetUidRequest, ULeaderboardUidResponse>(
	const int64&, UGetUidRequest*, FOnGetUidSuccess, FOnGetUidError, FOnGetUidComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UGetUidRequest, ULeaderboardUidResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetUidRequest*, FOnGetUidSuccess, FOnGetUidError, FOnGetUidComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UGetUidRequest*, TBeamFullResponseHandler<UGetUidRequest*, ULeaderboardUidResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetUidRequest*,
                                                                                   TBeamFullResponseHandler<UGetUidRequest*, ULeaderboardUidResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UDeleteEntriesRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UDeleteEntriesRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UDeleteEntriesRequest, UCommonResponse>(
	const int64&, UDeleteEntriesRequest*, FOnDeleteEntriesSuccess, FOnDeleteEntriesError, FOnDeleteEntriesComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UDeleteEntriesRequest, UCommonResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UDeleteEntriesRequest*, FOnDeleteEntriesSuccess, FOnDeleteEntriesError, FOnDeleteEntriesComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UDeleteEntriesRequest*, TBeamFullResponseHandler<UDeleteEntriesRequest*, UCommonResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UDeleteEntriesRequest*,
                                                                                   TBeamFullResponseHandler<UDeleteEntriesRequest*, UCommonResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UGetMembershipRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UGetMembershipRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UGetMembershipRequest, ULeaderboardMembershipResponse>(
	const int64&, UGetMembershipRequest*, FOnGetMembershipSuccess, FOnGetMembershipError, FOnGetMembershipComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UGetMembershipRequest, ULeaderboardMembershipResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetMembershipRequest*, FOnGetMembershipSuccess, FOnGetMembershipError, FOnGetMembershipComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UGetMembershipRequest*, TBeamFullResponseHandler<UGetMembershipRequest*, ULeaderboardMembershipResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetMembershipRequest*,
                                                                                   TBeamFullResponseHandler<UGetMembershipRequest*, ULeaderboardMembershipResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UGetPartitionRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UGetPartitionRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UGetPartitionRequest, ULeaderboardPartitionInfo>(
	const int64&, UGetPartitionRequest*, FOnGetPartitionSuccess, FOnGetPartitionError, FOnGetPartitionComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UGetPartitionRequest, ULeaderboardPartitionInfo>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetPartitionRequest*, FOnGetPartitionSuccess, FOnGetPartitionError, FOnGetPartitionComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UGetPartitionRequest*, TBeamFullResponseHandler<UGetPartitionRequest*, ULeaderboardPartitionInfo*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetPartitionRequest*,
                                                                                   TBeamFullResponseHandler<UGetPartitionRequest*, ULeaderboardPartitionInfo*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UGetFriendsRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UGetFriendsRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UGetFriendsRequest, ULeaderBoardViewResponse>(
	const int64&, UGetFriendsRequest*, FOnGetFriendsSuccess, FOnGetFriendsError, FOnGetFriendsComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UGetFriendsRequest, ULeaderBoardViewResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetFriendsRequest*, FOnGetFriendsSuccess, FOnGetFriendsError, FOnGetFriendsComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UGetFriendsRequest*, TBeamFullResponseHandler<UGetFriendsRequest*, ULeaderBoardViewResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetFriendsRequest*,
                                                                                   TBeamFullResponseHandler<UGetFriendsRequest*, ULeaderBoardViewResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPostLeaderboardsRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPostLeaderboardsRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPostLeaderboardsRequest, UCommonResponse>(
	const int64&, UPostLeaderboardsRequest*, FOnPostLeaderboardsSuccess, FOnPostLeaderboardsError, FOnPostLeaderboardsComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPostLeaderboardsRequest, UCommonResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostLeaderboardsRequest*, FOnPostLeaderboardsSuccess, FOnPostLeaderboardsError, FOnPostLeaderboardsComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPostLeaderboardsRequest*, TBeamFullResponseHandler<UPostLeaderboardsRequest*, UCommonResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostLeaderboardsRequest*,
                                                                                   TBeamFullResponseHandler<UPostLeaderboardsRequest*, UCommonResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UDeleteLeaderboardsRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UDeleteLeaderboardsRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UDeleteLeaderboardsRequest, UCommonResponse>(
	const int64&, UDeleteLeaderboardsRequest*, FOnDeleteLeaderboardsSuccess, FOnDeleteLeaderboardsError, FOnDeleteLeaderboardsComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UDeleteLeaderboardsRequest, UCommonResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UDeleteLeaderboardsRequest*, FOnDeleteLeaderboardsSuccess, FOnDeleteLeaderboardsError, FOnDeleteLeaderboardsComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UDeleteLeaderboardsRequest*, TBeamFullResponseHandler<UDeleteLeaderboardsRequest*, UCommonResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UDeleteLeaderboardsRequest*,
                                                                                   TBeamFullResponseHandler<UDeleteLeaderboardsRequest*, UCommonResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UObjectLeaderboardsGetAssignmentRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UObjectLeaderboardsGetAssignmentRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UObjectLeaderboardsGetAssignmentRequest, ULeaderboardAssignmentInfo>(
	const int64&, UObjectLeaderboardsGetAssignmentRequest*, FOnObjectLeaderboardsGetAssignmentSuccess, FOnObjectLeaderboardsGetAssignmentError, FOnObjectLeaderboardsGetAssignmentComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UObjectLeaderboardsGetAssignmentRequest, ULeaderboardAssignmentInfo>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UObjectLeaderboardsGetAssignmentRequest*, FOnObjectLeaderboardsGetAssignmentSuccess, FOnObjectLeaderboardsGetAssignmentError, FOnObjectLeaderboardsGetAssignmentComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UObjectLeaderboardsGetAssignmentRequest*, TBeamFullResponseHandler<UObjectLeaderboardsGetAssignmentRequest*, ULeaderboardAssignmentInfo*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UObjectLeaderboardsGetAssignmentRequest*,
                                                                                   TBeamFullResponseHandler<UObjectLeaderboardsGetAssignmentRequest*, ULeaderboardAssignmentInfo*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UDeleteAssignmentRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UDeleteAssignmentRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UDeleteAssignmentRequest, UCommonResponse>(
	const int64&, UDeleteAssignmentRequest*, FOnDeleteAssignmentSuccess, FOnDeleteAssignmentError, FOnDeleteAssignmentComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UDeleteAssignmentRequest, UCommonResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UDeleteAssignmentRequest*, FOnDeleteAssignmentSuccess, FOnDeleteAssignmentError, FOnDeleteAssignmentComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UDeleteAssignmentRequest*, TBeamFullResponseHandler<UDeleteAssignmentRequest*, UCommonResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UDeleteAssignmentRequest*,
                                                                                   TBeamFullResponseHandler<UDeleteAssignmentRequest*, UCommonResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UDeleteEntryRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UDeleteEntryRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UDeleteEntryRequest, UCommonResponse>(
	const int64&, UDeleteEntryRequest*, FOnDeleteEntrySuccess, FOnDeleteEntryError, FOnDeleteEntryComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UDeleteEntryRequest, UCommonResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UDeleteEntryRequest*, FOnDeleteEntrySuccess, FOnDeleteEntryError, FOnDeleteEntryComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UDeleteEntryRequest*, TBeamFullResponseHandler<UDeleteEntryRequest*, UCommonResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UDeleteEntryRequest*,
                                                                                   TBeamFullResponseHandler<UDeleteEntryRequest*, UCommonResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPutFreezeRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPutFreezeRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPutFreezeRequest, UCommonResponse>(
	const int64&, UPutFreezeRequest*, FOnPutFreezeSuccess, FOnPutFreezeError, FOnPutFreezeComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPutFreezeRequest, UCommonResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPutFreezeRequest*, FOnPutFreezeSuccess, FOnPutFreezeError, FOnPutFreezeComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPutFreezeRequest*, TBeamFullResponseHandler<UPutFreezeRequest*, UCommonResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPutFreezeRequest*,
                                                                                   TBeamFullResponseHandler<UPutFreezeRequest*, UCommonResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UGetDetailsRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UGetDetailsRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UGetDetailsRequest, ULeaderboardDetails>(
	const int64&, UGetDetailsRequest*, FOnGetDetailsSuccess, FOnGetDetailsError, FOnGetDetailsComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UGetDetailsRequest, ULeaderboardDetails>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetDetailsRequest*, FOnGetDetailsSuccess, FOnGetDetailsError, FOnGetDetailsComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UGetDetailsRequest*, TBeamFullResponseHandler<UGetDetailsRequest*, ULeaderboardDetails*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetDetailsRequest*,
                                                                                   TBeamFullResponseHandler<UGetDetailsRequest*, ULeaderboardDetails*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPutSwapRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPutSwapRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPutSwapRequest, UCommonResponse>(
	const int64&, UPutSwapRequest*, FOnPutSwapSuccess, FOnPutSwapError, FOnPutSwapComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPutSwapRequest, UCommonResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPutSwapRequest*, FOnPutSwapSuccess, FOnPutSwapError, FOnPutSwapComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPutSwapRequest*, TBeamFullResponseHandler<UPutSwapRequest*, UCommonResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPutSwapRequest*,
                                                                                   TBeamFullResponseHandler<UPutSwapRequest*, UCommonResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UGetGetPersonallyIdentifiableInformationRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UGetGetPersonallyIdentifiableInformationRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UGetGetPersonallyIdentifiableInformationRequest, UAccountPersonallyIdentifiableInformationResponse>(
	const int64&, UGetGetPersonallyIdentifiableInformationRequest*, FOnGetGetPersonallyIdentifiableInformationSuccess, FOnGetGetPersonallyIdentifiableInformationError, FOnGetGetPersonallyIdentifiableInformationComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UGetGetPersonallyIdentifiableInformationRequest, UAccountPersonallyIdentifiableInformationResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetGetPersonallyIdentifiableInformationRequest*, FOnGetGetPersonallyIdentifiableInformationSuccess, FOnGetGetPersonallyIdentifiableInformationError, FOnGetGetPersonallyIdentifiableInformationComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UGetGetPersonallyIdentifiableInformationRequest*, TBeamFullResponseHandler<UGetGetPersonallyIdentifiableInformationRequest*, UAccountPersonallyIdentifiableInformationResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetGetPersonallyIdentifiableInformationRequest*,
                                                                                   TBeamFullResponseHandler<UGetGetPersonallyIdentifiableInformationRequest*, UAccountPersonallyIdentifiableInformationResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UGetAvailableThirdPartyRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UGetAvailableThirdPartyRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UGetAvailableThirdPartyRequest, UAccountAvailableResponse>(
	const int64&, UGetAvailableThirdPartyRequest*, FOnGetAvailableThirdPartySuccess, FOnGetAvailableThirdPartyError, FOnGetAvailableThirdPartyComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UGetAvailableThirdPartyRequest, UAccountAvailableResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetAvailableThirdPartyRequest*, FOnGetAvailableThirdPartySuccess, FOnGetAvailableThirdPartyError, FOnGetAvailableThirdPartyComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UGetAvailableThirdPartyRequest*, TBeamFullResponseHandler<UGetAvailableThirdPartyRequest*, UAccountAvailableResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetAvailableThirdPartyRequest*,
                                                                                   TBeamFullResponseHandler<UGetAvailableThirdPartyRequest*, UAccountAvailableResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPostPasswordUpdateInitRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPostPasswordUpdateInitRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPostPasswordUpdateInitRequest, UEmptyResponse>(
	const int64&, UPostPasswordUpdateInitRequest*, FOnPostPasswordUpdateInitSuccess, FOnPostPasswordUpdateInitError, FOnPostPasswordUpdateInitComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPostPasswordUpdateInitRequest, UEmptyResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostPasswordUpdateInitRequest*, FOnPostPasswordUpdateInitSuccess, FOnPostPasswordUpdateInitError, FOnPostPasswordUpdateInitComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPostPasswordUpdateInitRequest*, TBeamFullResponseHandler<UPostPasswordUpdateInitRequest*, UEmptyResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostPasswordUpdateInitRequest*,
                                                                                   TBeamFullResponseHandler<UPostPasswordUpdateInitRequest*, UEmptyResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UGetAvailableDeviceIdRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UGetAvailableDeviceIdRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UGetAvailableDeviceIdRequest, UAccountAvailableResponse>(
	const int64&, UGetAvailableDeviceIdRequest*, FOnGetAvailableDeviceIdSuccess, FOnGetAvailableDeviceIdError, FOnGetAvailableDeviceIdComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UGetAvailableDeviceIdRequest, UAccountAvailableResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetAvailableDeviceIdRequest*, FOnGetAvailableDeviceIdSuccess, FOnGetAvailableDeviceIdError, FOnGetAvailableDeviceIdComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UGetAvailableDeviceIdRequest*, TBeamFullResponseHandler<UGetAvailableDeviceIdRequest*, UAccountAvailableResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetAvailableDeviceIdRequest*,
                                                                                   TBeamFullResponseHandler<UGetAvailableDeviceIdRequest*, UAccountAvailableResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UGetAvailableRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UGetAvailableRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UGetAvailableRequest, UAccountAvailableResponse>(
	const int64&, UGetAvailableRequest*, FOnGetAvailableSuccess, FOnGetAvailableError, FOnGetAvailableComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UGetAvailableRequest, UAccountAvailableResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetAvailableRequest*, FOnGetAvailableSuccess, FOnGetAvailableError, FOnGetAvailableComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UGetAvailableRequest*, TBeamFullResponseHandler<UGetAvailableRequest*, UAccountAvailableResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetAvailableRequest*,
                                                                                   TBeamFullResponseHandler<UGetAvailableRequest*, UAccountAvailableResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPostPasswordUpdateConfirmRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPostPasswordUpdateConfirmRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPostPasswordUpdateConfirmRequest, UEmptyResponse>(
	const int64&, UPostPasswordUpdateConfirmRequest*, FOnPostPasswordUpdateConfirmSuccess, FOnPostPasswordUpdateConfirmError, FOnPostPasswordUpdateConfirmComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPostPasswordUpdateConfirmRequest, UEmptyResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostPasswordUpdateConfirmRequest*, FOnPostPasswordUpdateConfirmSuccess, FOnPostPasswordUpdateConfirmError, FOnPostPasswordUpdateConfirmComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPostPasswordUpdateConfirmRequest*, TBeamFullResponseHandler<UPostPasswordUpdateConfirmRequest*, UEmptyResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostPasswordUpdateConfirmRequest*,
                                                                                   TBeamFullResponseHandler<UPostPasswordUpdateConfirmRequest*, UEmptyResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UGetAvailableRolesRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UGetAvailableRolesRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UGetAvailableRolesRequest, UAvailableRolesResponse>(
	const int64&, UGetAvailableRolesRequest*, FOnGetAvailableRolesSuccess, FOnGetAvailableRolesError, FOnGetAvailableRolesComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UGetAvailableRolesRequest, UAvailableRolesResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetAvailableRolesRequest*, FOnGetAvailableRolesSuccess, FOnGetAvailableRolesError, FOnGetAvailableRolesComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UGetAvailableRolesRequest*, TBeamFullResponseHandler<UGetAvailableRolesRequest*, UAvailableRolesResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetAvailableRolesRequest*,
                                                                                   TBeamFullResponseHandler<UGetAvailableRolesRequest*, UAvailableRolesResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UDeleteMeDeviceRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UDeleteMeDeviceRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UDeleteMeDeviceRequest, UAccountPlayerView>(
	const int64&, UDeleteMeDeviceRequest*, FOnDeleteMeDeviceSuccess, FOnDeleteMeDeviceError, FOnDeleteMeDeviceComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UDeleteMeDeviceRequest, UAccountPlayerView>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UDeleteMeDeviceRequest*, FOnDeleteMeDeviceSuccess, FOnDeleteMeDeviceError, FOnDeleteMeDeviceComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UDeleteMeDeviceRequest*, TBeamFullResponseHandler<UDeleteMeDeviceRequest*, UAccountPlayerView*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UDeleteMeDeviceRequest*,
                                                                                   TBeamFullResponseHandler<UDeleteMeDeviceRequest*, UAccountPlayerView*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UBasicAccountsGetMeRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UBasicAccountsGetMeRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UBasicAccountsGetMeRequest, UAccountPlayerView>(
	const int64&, UBasicAccountsGetMeRequest*, FOnBasicAccountsGetMeSuccess, FOnBasicAccountsGetMeError, FOnBasicAccountsGetMeComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UBasicAccountsGetMeRequest, UAccountPlayerView>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UBasicAccountsGetMeRequest*, FOnBasicAccountsGetMeSuccess, FOnBasicAccountsGetMeError, FOnBasicAccountsGetMeComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UBasicAccountsGetMeRequest*, TBeamFullResponseHandler<UBasicAccountsGetMeRequest*, UAccountPlayerView*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UBasicAccountsGetMeRequest*,
                                                                                   TBeamFullResponseHandler<UBasicAccountsGetMeRequest*, UAccountPlayerView*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPutMeRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPutMeRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPutMeRequest, UAccountPlayerView>(
	const int64&, UPutMeRequest*, FOnPutMeSuccess, FOnPutMeError, FOnPutMeComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPutMeRequest, UAccountPlayerView>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPutMeRequest*, FOnPutMeSuccess, FOnPutMeError, FOnPutMeComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPutMeRequest*, TBeamFullResponseHandler<UPutMeRequest*, UAccountPlayerView*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPutMeRequest*,
                                                                                   TBeamFullResponseHandler<UPutMeRequest*, UAccountPlayerView*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UDeleteMeThirdPartyRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UDeleteMeThirdPartyRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UDeleteMeThirdPartyRequest, UAccountPlayerView>(
	const int64&, UDeleteMeThirdPartyRequest*, FOnDeleteMeThirdPartySuccess, FOnDeleteMeThirdPartyError, FOnDeleteMeThirdPartyComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UDeleteMeThirdPartyRequest, UAccountPlayerView>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UDeleteMeThirdPartyRequest*, FOnDeleteMeThirdPartySuccess, FOnDeleteMeThirdPartyError, FOnDeleteMeThirdPartyComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UDeleteMeThirdPartyRequest*, TBeamFullResponseHandler<UDeleteMeThirdPartyRequest*, UAccountPlayerView*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UDeleteMeThirdPartyRequest*,
                                                                                   TBeamFullResponseHandler<UDeleteMeThirdPartyRequest*, UAccountPlayerView*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UBasicAccountsGetSearchRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UBasicAccountsGetSearchRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UBasicAccountsGetSearchRequest, UAccountSearchResponse>(
	const int64&, UBasicAccountsGetSearchRequest*, FOnBasicAccountsGetSearchSuccess, FOnBasicAccountsGetSearchError, FOnBasicAccountsGetSearchComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UBasicAccountsGetSearchRequest, UAccountSearchResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UBasicAccountsGetSearchRequest*, FOnBasicAccountsGetSearchSuccess, FOnBasicAccountsGetSearchError, FOnBasicAccountsGetSearchComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UBasicAccountsGetSearchRequest*, TBeamFullResponseHandler<UBasicAccountsGetSearchRequest*, UAccountSearchResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UBasicAccountsGetSearchRequest*,
                                                                                   TBeamFullResponseHandler<UBasicAccountsGetSearchRequest*, UAccountSearchResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPostEmailUpdateInitRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPostEmailUpdateInitRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPostEmailUpdateInitRequest, UEmptyResponse>(
	const int64&, UPostEmailUpdateInitRequest*, FOnPostEmailUpdateInitSuccess, FOnPostEmailUpdateInitError, FOnPostEmailUpdateInitComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPostEmailUpdateInitRequest, UEmptyResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostEmailUpdateInitRequest*, FOnPostEmailUpdateInitSuccess, FOnPostEmailUpdateInitError, FOnPostEmailUpdateInitComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPostEmailUpdateInitRequest*, TBeamFullResponseHandler<UPostEmailUpdateInitRequest*, UEmptyResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostEmailUpdateInitRequest*,
                                                                                   TBeamFullResponseHandler<UPostEmailUpdateInitRequest*, UEmptyResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPostEmailUpdateConfirmRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPostEmailUpdateConfirmRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPostEmailUpdateConfirmRequest, UEmptyResponse>(
	const int64&, UPostEmailUpdateConfirmRequest*, FOnPostEmailUpdateConfirmSuccess, FOnPostEmailUpdateConfirmError, FOnPostEmailUpdateConfirmComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPostEmailUpdateConfirmRequest, UEmptyResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostEmailUpdateConfirmRequest*, FOnPostEmailUpdateConfirmSuccess, FOnPostEmailUpdateConfirmError, FOnPostEmailUpdateConfirmComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPostEmailUpdateConfirmRequest*, TBeamFullResponseHandler<UPostEmailUpdateConfirmRequest*, UEmptyResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostEmailUpdateConfirmRequest*,
                                                                                   TBeamFullResponseHandler<UPostEmailUpdateConfirmRequest*, UEmptyResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPostAdminAdminUserRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPostAdminAdminUserRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPostAdminAdminUserRequest, UAccountPortalView>(
	const int64&, UPostAdminAdminUserRequest*, FOnPostAdminAdminUserSuccess, FOnPostAdminAdminUserError, FOnPostAdminAdminUserComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPostAdminAdminUserRequest, UAccountPortalView>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostAdminAdminUserRequest*, FOnPostAdminAdminUserSuccess, FOnPostAdminAdminUserError, FOnPostAdminAdminUserComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPostAdminAdminUserRequest*, TBeamFullResponseHandler<UPostAdminAdminUserRequest*, UAccountPortalView*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostAdminAdminUserRequest*,
                                                                                   TBeamFullResponseHandler<UPostAdminAdminUserRequest*, UAccountPortalView*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UBasicAccountsPostRegisterRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UBasicAccountsPostRegisterRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UBasicAccountsPostRegisterRequest, UAccountPlayerView>(
	const int64&, UBasicAccountsPostRegisterRequest*, FOnBasicAccountsPostRegisterSuccess, FOnBasicAccountsPostRegisterError, FOnBasicAccountsPostRegisterComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UBasicAccountsPostRegisterRequest, UAccountPlayerView>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UBasicAccountsPostRegisterRequest*, FOnBasicAccountsPostRegisterSuccess, FOnBasicAccountsPostRegisterError, FOnBasicAccountsPostRegisterComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UBasicAccountsPostRegisterRequest*, TBeamFullResponseHandler<UBasicAccountsPostRegisterRequest*, UAccountPlayerView*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UBasicAccountsPostRegisterRequest*,
                                                                                   TBeamFullResponseHandler<UBasicAccountsPostRegisterRequest*, UAccountPlayerView*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UGetAdminMeRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UGetAdminMeRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UGetAdminMeRequest, UAccountPortalView>(
	const int64&, UGetAdminMeRequest*, FOnGetAdminMeSuccess, FOnGetAdminMeError, FOnGetAdminMeComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UGetAdminMeRequest, UAccountPortalView>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetAdminMeRequest*, FOnGetAdminMeSuccess, FOnGetAdminMeError, FOnGetAdminMeComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UGetAdminMeRequest*, TBeamFullResponseHandler<UGetAdminMeRequest*, UAccountPortalView*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetAdminMeRequest*,
                                                                                   TBeamFullResponseHandler<UGetAdminMeRequest*, UAccountPortalView*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UGetAdminAdminUsersRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UGetAdminAdminUsersRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UGetAdminAdminUsersRequest, UGetAdminsResponse>(
	const int64&, UGetAdminAdminUsersRequest*, FOnGetAdminAdminUsersSuccess, FOnGetAdminAdminUsersError, FOnGetAdminAdminUsersComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UGetAdminAdminUsersRequest, UGetAdminsResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetAdminAdminUsersRequest*, FOnGetAdminAdminUsersSuccess, FOnGetAdminAdminUsersError, FOnGetAdminAdminUsersComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UGetAdminAdminUsersRequest*, TBeamFullResponseHandler<UGetAdminAdminUsersRequest*, UGetAdminsResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetAdminAdminUsersRequest*,
                                                                                   TBeamFullResponseHandler<UGetAdminAdminUsersRequest*, UGetAdminsResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UGetFindRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UGetFindRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UGetFindRequest, UAccountsBasicAccount>(
	const int64&, UGetFindRequest*, FOnGetFindSuccess, FOnGetFindError, FOnGetFindComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UGetFindRequest, UAccountsBasicAccount>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetFindRequest*, FOnGetFindSuccess, FOnGetFindError, FOnGetFindComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UGetFindRequest*, TBeamFullResponseHandler<UGetFindRequest*, UAccountsBasicAccount*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetFindRequest*,
                                                                                   TBeamFullResponseHandler<UGetFindRequest*, UAccountsBasicAccount*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPutAdminEmailRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPutAdminEmailRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPutAdminEmailRequest, UAccountsObjectAccount>(
	const int64&, UPutAdminEmailRequest*, FOnPutAdminEmailSuccess, FOnPutAdminEmailError, FOnPutAdminEmailComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPutAdminEmailRequest, UAccountsObjectAccount>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPutAdminEmailRequest*, FOnPutAdminEmailSuccess, FOnPutAdminEmailError, FOnPutAdminEmailComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPutAdminEmailRequest*, TBeamFullResponseHandler<UPutAdminEmailRequest*, UAccountsObjectAccount*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPutAdminEmailRequest*,
                                                                                   TBeamFullResponseHandler<UPutAdminEmailRequest*, UAccountsObjectAccount*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UGetRoleReportRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UGetRoleReportRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UGetRoleReportRequest, UAccountRolesReport>(
	const int64&, UGetRoleReportRequest*, FOnGetRoleReportSuccess, FOnGetRoleReportError, FOnGetRoleReportComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UGetRoleReportRequest, UAccountRolesReport>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetRoleReportRequest*, FOnGetRoleReportSuccess, FOnGetRoleReportError, FOnGetRoleReportComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UGetRoleReportRequest*, TBeamFullResponseHandler<UGetRoleReportRequest*, UAccountRolesReport*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetRoleReportRequest*,
                                                                                   TBeamFullResponseHandler<UGetRoleReportRequest*, UAccountRolesReport*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UObjectAccountsPutRoleRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UObjectAccountsPutRoleRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UObjectAccountsPutRoleRequest, UEmptyResponse>(
	const int64&, UObjectAccountsPutRoleRequest*, FOnObjectAccountsPutRoleSuccess, FOnObjectAccountsPutRoleError, FOnObjectAccountsPutRoleComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UObjectAccountsPutRoleRequest, UEmptyResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UObjectAccountsPutRoleRequest*, FOnObjectAccountsPutRoleSuccess, FOnObjectAccountsPutRoleError, FOnObjectAccountsPutRoleComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UObjectAccountsPutRoleRequest*, TBeamFullResponseHandler<UObjectAccountsPutRoleRequest*, UEmptyResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UObjectAccountsPutRoleRequest*,
                                                                                   TBeamFullResponseHandler<UObjectAccountsPutRoleRequest*, UEmptyResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UDeleteRoleRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UDeleteRoleRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UDeleteRoleRequest, UEmptyResponse>(
	const int64&, UDeleteRoleRequest*, FOnDeleteRoleSuccess, FOnDeleteRoleError, FOnDeleteRoleComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UDeleteRoleRequest, UEmptyResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UDeleteRoleRequest*, FOnDeleteRoleSuccess, FOnDeleteRoleError, FOnDeleteRoleComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UDeleteRoleRequest*, TBeamFullResponseHandler<UDeleteRoleRequest*, UEmptyResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UDeleteRoleRequest*,
                                                                                   TBeamFullResponseHandler<UDeleteRoleRequest*, UEmptyResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPutAdminScopeRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPutAdminScopeRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPutAdminScopeRequest, UEmptyResponse>(
	const int64&, UPutAdminScopeRequest*, FOnPutAdminScopeSuccess, FOnPutAdminScopeError, FOnPutAdminScopeComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPutAdminScopeRequest, UEmptyResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPutAdminScopeRequest*, FOnPutAdminScopeSuccess, FOnPutAdminScopeError, FOnPutAdminScopeComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPutAdminScopeRequest*, TBeamFullResponseHandler<UPutAdminScopeRequest*, UEmptyResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPutAdminScopeRequest*,
                                                                                   TBeamFullResponseHandler<UPutAdminScopeRequest*, UEmptyResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UDeleteAdminScopeRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UDeleteAdminScopeRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UDeleteAdminScopeRequest, UEmptyResponse>(
	const int64&, UDeleteAdminScopeRequest*, FOnDeleteAdminScopeSuccess, FOnDeleteAdminScopeError, FOnDeleteAdminScopeComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UDeleteAdminScopeRequest, UEmptyResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UDeleteAdminScopeRequest*, FOnDeleteAdminScopeSuccess, FOnDeleteAdminScopeError, FOnDeleteAdminScopeComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UDeleteAdminScopeRequest*, TBeamFullResponseHandler<UDeleteAdminScopeRequest*, UEmptyResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UDeleteAdminScopeRequest*,
                                                                                   TBeamFullResponseHandler<UDeleteAdminScopeRequest*, UEmptyResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPutAdminThirdPartyRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPutAdminThirdPartyRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPutAdminThirdPartyRequest, UEmptyResponse>(
	const int64&, UPutAdminThirdPartyRequest*, FOnPutAdminThirdPartySuccess, FOnPutAdminThirdPartyError, FOnPutAdminThirdPartyComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPutAdminThirdPartyRequest, UEmptyResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPutAdminThirdPartyRequest*, FOnPutAdminThirdPartySuccess, FOnPutAdminThirdPartyError, FOnPutAdminThirdPartyComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPutAdminThirdPartyRequest*, TBeamFullResponseHandler<UPutAdminThirdPartyRequest*, UEmptyResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPutAdminThirdPartyRequest*,
                                                                                   TBeamFullResponseHandler<UPutAdminThirdPartyRequest*, UEmptyResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UDeleteAdminThirdPartyRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UDeleteAdminThirdPartyRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UDeleteAdminThirdPartyRequest, UEmptyResponse>(
	const int64&, UDeleteAdminThirdPartyRequest*, FOnDeleteAdminThirdPartySuccess, FOnDeleteAdminThirdPartyError, FOnDeleteAdminThirdPartyComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UDeleteAdminThirdPartyRequest, UEmptyResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UDeleteAdminThirdPartyRequest*, FOnDeleteAdminThirdPartySuccess, FOnDeleteAdminThirdPartyError, FOnDeleteAdminThirdPartyComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UDeleteAdminThirdPartyRequest*, TBeamFullResponseHandler<UDeleteAdminThirdPartyRequest*, UEmptyResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UDeleteAdminThirdPartyRequest*,
                                                                                   TBeamFullResponseHandler<UDeleteAdminThirdPartyRequest*, UEmptyResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPutAccountsRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPutAccountsRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPutAccountsRequest, UAccountsObjectAccount>(
	const int64&, UPutAccountsRequest*, FOnPutAccountsSuccess, FOnPutAccountsError, FOnPutAccountsComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPutAccountsRequest, UAccountsObjectAccount>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPutAccountsRequest*, FOnPutAccountsSuccess, FOnPutAccountsError, FOnPutAccountsComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPutAccountsRequest*, TBeamFullResponseHandler<UPutAccountsRequest*, UAccountsObjectAccount*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPutAccountsRequest*,
                                                                                   TBeamFullResponseHandler<UPutAccountsRequest*, UAccountsObjectAccount*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UDeleteAdminForgetRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UDeleteAdminForgetRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UDeleteAdminForgetRequest, UAccountsObjectAccount>(
	const int64&, UDeleteAdminForgetRequest*, FOnDeleteAdminForgetSuccess, FOnDeleteAdminForgetError, FOnDeleteAdminForgetComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UDeleteAdminForgetRequest, UAccountsObjectAccount>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UDeleteAdminForgetRequest*, FOnDeleteAdminForgetSuccess, FOnDeleteAdminForgetError, FOnDeleteAdminForgetComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UDeleteAdminForgetRequest*, TBeamFullResponseHandler<UDeleteAdminForgetRequest*, UAccountsObjectAccount*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UDeleteAdminForgetRequest*,
                                                                                   TBeamFullResponseHandler<UDeleteAdminForgetRequest*, UAccountsObjectAccount*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UGetClientBatchRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UGetClientBatchRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UGetClientBatchRequest, UBatchReadStatsResponse>(
	const int64&, UGetClientBatchRequest*, FOnGetClientBatchSuccess, FOnGetClientBatchError, FOnGetClientBatchComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UGetClientBatchRequest, UBatchReadStatsResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetClientBatchRequest*, FOnGetClientBatchSuccess, FOnGetClientBatchError, FOnGetClientBatchComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UGetClientBatchRequest*, TBeamFullResponseHandler<UGetClientBatchRequest*, UBatchReadStatsResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetClientBatchRequest*,
                                                                                   TBeamFullResponseHandler<UGetClientBatchRequest*, UBatchReadStatsResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPostClientStringlistRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPostClientStringlistRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPostClientStringlistRequest, UEmptyResponse>(
	const int64&, UPostClientStringlistRequest*, FOnPostClientStringlistSuccess, FOnPostClientStringlistError, FOnPostClientStringlistComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPostClientStringlistRequest, UEmptyResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostClientStringlistRequest*, FOnPostClientStringlistSuccess, FOnPostClientStringlistError, FOnPostClientStringlistComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPostClientStringlistRequest*, TBeamFullResponseHandler<UPostClientStringlistRequest*, UEmptyResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostClientStringlistRequest*,
                                                                                   TBeamFullResponseHandler<UPostClientStringlistRequest*, UEmptyResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UGetClientRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UGetClientRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UGetClientRequest, UStatsResponse>(
	const int64&, UGetClientRequest*, FOnGetClientSuccess, FOnGetClientError, FOnGetClientComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UGetClientRequest, UStatsResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetClientRequest*, FOnGetClientSuccess, FOnGetClientError, FOnGetClientComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UGetClientRequest*, TBeamFullResponseHandler<UGetClientRequest*, UStatsResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetClientRequest*,
                                                                                   TBeamFullResponseHandler<UGetClientRequest*, UStatsResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPostClientRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPostClientRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPostClientRequest, UEmptyResponse>(
	const int64&, UPostClientRequest*, FOnPostClientSuccess, FOnPostClientError, FOnPostClientComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPostClientRequest, UEmptyResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostClientRequest*, FOnPostClientSuccess, FOnPostClientError, FOnPostClientComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPostClientRequest*, TBeamFullResponseHandler<UPostClientRequest*, UEmptyResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostClientRequest*,
                                                                                   TBeamFullResponseHandler<UPostClientRequest*, UEmptyResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPutSubscribeRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPutSubscribeRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPutSubscribeRequest, UCommonResponse>(
	const int64&, UPutSubscribeRequest*, FOnPutSubscribeSuccess, FOnPutSubscribeError, FOnPutSubscribeComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPutSubscribeRequest, UCommonResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPutSubscribeRequest*, FOnPutSubscribeSuccess, FOnPutSubscribeError, FOnPutSubscribeComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPutSubscribeRequest*, TBeamFullResponseHandler<UPutSubscribeRequest*, UCommonResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPutSubscribeRequest*,
                                                                                   TBeamFullResponseHandler<UPutSubscribeRequest*, UCommonResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPostBatchRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPostBatchRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPostBatchRequest, UEmptyResponse>(
	const int64&, UPostBatchRequest*, FOnPostBatchSuccess, FOnPostBatchError, FOnPostBatchComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPostBatchRequest, UEmptyResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostBatchRequest*, FOnPostBatchSuccess, FOnPostBatchError, FOnPostBatchComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPostBatchRequest*, TBeamFullResponseHandler<UPostBatchRequest*, UEmptyResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostBatchRequest*,
                                                                                   TBeamFullResponseHandler<UPostBatchRequest*, UEmptyResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UBasicStatsPostSearchRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UBasicStatsPostSearchRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UBasicStatsPostSearchRequest, UStatsSearchResponse>(
	const int64&, UBasicStatsPostSearchRequest*, FOnBasicStatsPostSearchSuccess, FOnBasicStatsPostSearchError, FOnBasicStatsPostSearchComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UBasicStatsPostSearchRequest, UStatsSearchResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UBasicStatsPostSearchRequest*, FOnBasicStatsPostSearchSuccess, FOnBasicStatsPostSearchError, FOnBasicStatsPostSearchComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UBasicStatsPostSearchRequest*, TBeamFullResponseHandler<UBasicStatsPostSearchRequest*, UStatsSearchResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UBasicStatsPostSearchRequest*,
                                                                                   TBeamFullResponseHandler<UBasicStatsPostSearchRequest*, UStatsSearchResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPostSearchExtendedRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPostSearchExtendedRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPostSearchExtendedRequest, USearchExtendedResponse>(
	const int64&, UPostSearchExtendedRequest*, FOnPostSearchExtendedSuccess, FOnPostSearchExtendedError, FOnPostSearchExtendedComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPostSearchExtendedRequest, USearchExtendedResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostSearchExtendedRequest*, FOnPostSearchExtendedSuccess, FOnPostSearchExtendedError, FOnPostSearchExtendedComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPostSearchExtendedRequest*, TBeamFullResponseHandler<UPostSearchExtendedRequest*, USearchExtendedResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostSearchExtendedRequest*,
                                                                                   TBeamFullResponseHandler<UPostSearchExtendedRequest*, USearchExtendedResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UGetStatsRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UGetStatsRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UGetStatsRequest, UStatsResponse>(
	const int64&, UGetStatsRequest*, FOnGetStatsSuccess, FOnGetStatsError, FOnGetStatsComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UGetStatsRequest, UStatsResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetStatsRequest*, FOnGetStatsSuccess, FOnGetStatsError, FOnGetStatsComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UGetStatsRequest*, TBeamFullResponseHandler<UGetStatsRequest*, UStatsResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetStatsRequest*,
                                                                                   TBeamFullResponseHandler<UGetStatsRequest*, UStatsResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPostStatsRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPostStatsRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPostStatsRequest, UEmptyResponse>(
	const int64&, UPostStatsRequest*, FOnPostStatsSuccess, FOnPostStatsError, FOnPostStatsComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPostStatsRequest, UEmptyResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostStatsRequest*, FOnPostStatsSuccess, FOnPostStatsError, FOnPostStatsComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPostStatsRequest*, TBeamFullResponseHandler<UPostStatsRequest*, UEmptyResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostStatsRequest*,
                                                                                   TBeamFullResponseHandler<UPostStatsRequest*, UEmptyResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UDeleteStatsRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UDeleteStatsRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UDeleteStatsRequest, UEmptyResponse>(
	const int64&, UDeleteStatsRequest*, FOnDeleteStatsSuccess, FOnDeleteStatsError, FOnDeleteStatsComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UDeleteStatsRequest, UEmptyResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UDeleteStatsRequest*, FOnDeleteStatsSuccess, FOnDeleteStatsError, FOnDeleteStatsComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UDeleteStatsRequest*, TBeamFullResponseHandler<UDeleteStatsRequest*, UEmptyResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UDeleteStatsRequest*,
                                                                                   TBeamFullResponseHandler<UDeleteStatsRequest*, UEmptyResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPostSearchGroupsRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPostSearchGroupsRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPostSearchGroupsRequest, UGetStatusForGroupsResponse>(
	const int64&, UPostSearchGroupsRequest*, FOnPostSearchGroupsSuccess, FOnPostSearchGroupsError, FOnPostSearchGroupsComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPostSearchGroupsRequest, UGetStatusForGroupsResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostSearchGroupsRequest*, FOnPostSearchGroupsSuccess, FOnPostSearchGroupsError, FOnPostSearchGroupsComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPostSearchGroupsRequest*, TBeamFullResponseHandler<UPostSearchGroupsRequest*, UGetStatusForGroupsResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostSearchGroupsRequest*,
                                                                                   TBeamFullResponseHandler<UPostSearchGroupsRequest*, UGetStatusForGroupsResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UBasicTournamentsGetTournamentsRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UBasicTournamentsGetTournamentsRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UBasicTournamentsGetTournamentsRequest, UTournamentQueryResponse>(
	const int64&, UBasicTournamentsGetTournamentsRequest*, FOnBasicTournamentsGetTournamentsSuccess, FOnBasicTournamentsGetTournamentsError, FOnBasicTournamentsGetTournamentsComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UBasicTournamentsGetTournamentsRequest, UTournamentQueryResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UBasicTournamentsGetTournamentsRequest*, FOnBasicTournamentsGetTournamentsSuccess, FOnBasicTournamentsGetTournamentsError, FOnBasicTournamentsGetTournamentsComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UBasicTournamentsGetTournamentsRequest*, TBeamFullResponseHandler<UBasicTournamentsGetTournamentsRequest*, UTournamentQueryResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UBasicTournamentsGetTournamentsRequest*,
                                                                                   TBeamFullResponseHandler<UBasicTournamentsGetTournamentsRequest*, UTournamentQueryResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPostScoreRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPostScoreRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPostScoreRequest, UEmptyResponse>(
	const int64&, UPostScoreRequest*, FOnPostScoreSuccess, FOnPostScoreError, FOnPostScoreComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPostScoreRequest, UEmptyResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostScoreRequest*, FOnPostScoreSuccess, FOnPostScoreError, FOnPostScoreComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPostScoreRequest*, TBeamFullResponseHandler<UPostScoreRequest*, UEmptyResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostScoreRequest*,
                                                                                   TBeamFullResponseHandler<UPostScoreRequest*, UEmptyResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UObjectTournamentsGetTournamentsRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UObjectTournamentsGetTournamentsRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UObjectTournamentsGetTournamentsRequest, UTournamentClientView>(
	const int64&, UObjectTournamentsGetTournamentsRequest*, FOnObjectTournamentsGetTournamentsSuccess, FOnObjectTournamentsGetTournamentsError, FOnObjectTournamentsGetTournamentsComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UObjectTournamentsGetTournamentsRequest, UTournamentClientView>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UObjectTournamentsGetTournamentsRequest*, FOnObjectTournamentsGetTournamentsSuccess, FOnObjectTournamentsGetTournamentsError, FOnObjectTournamentsGetTournamentsComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UObjectTournamentsGetTournamentsRequest*, TBeamFullResponseHandler<UObjectTournamentsGetTournamentsRequest*, UTournamentClientView*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UObjectTournamentsGetTournamentsRequest*,
                                                                                   TBeamFullResponseHandler<UObjectTournamentsGetTournamentsRequest*, UTournamentClientView*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPostTournamentsRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPostTournamentsRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPostTournamentsRequest, UPlayerStatus>(
	const int64&, UPostTournamentsRequest*, FOnPostTournamentsSuccess, FOnPostTournamentsError, FOnPostTournamentsComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPostTournamentsRequest, UPlayerStatus>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostTournamentsRequest*, FOnPostTournamentsSuccess, FOnPostTournamentsError, FOnPostTournamentsComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPostTournamentsRequest*, TBeamFullResponseHandler<UPostTournamentsRequest*, UPlayerStatus*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostTournamentsRequest*,
                                                                                   TBeamFullResponseHandler<UPostTournamentsRequest*, UPlayerStatus*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UGetMeGroupRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UGetMeGroupRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UGetMeGroupRequest, UGetGroupStatusResponse>(
	const int64&, UGetMeGroupRequest*, FOnGetMeGroupSuccess, FOnGetMeGroupError, FOnGetMeGroupComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UGetMeGroupRequest, UGetGroupStatusResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetMeGroupRequest*, FOnGetMeGroupSuccess, FOnGetMeGroupError, FOnGetMeGroupComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UGetMeGroupRequest*, TBeamFullResponseHandler<UGetMeGroupRequest*, UGetGroupStatusResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetMeGroupRequest*,
                                                                                   TBeamFullResponseHandler<UGetMeGroupRequest*, UGetGroupStatusResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UGetRewardsRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UGetRewardsRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UGetRewardsRequest, URewardsResponse>(
	const int64&, UGetRewardsRequest*, FOnGetRewardsSuccess, FOnGetRewardsError, FOnGetRewardsComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UGetRewardsRequest, URewardsResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetRewardsRequest*, FOnGetRewardsSuccess, FOnGetRewardsError, FOnGetRewardsComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UGetRewardsRequest*, TBeamFullResponseHandler<UGetRewardsRequest*, URewardsResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetRewardsRequest*,
                                                                                   TBeamFullResponseHandler<UGetRewardsRequest*, URewardsResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPostRewardsRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPostRewardsRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPostRewardsRequest, URewardsResponse>(
	const int64&, UPostRewardsRequest*, FOnPostRewardsSuccess, FOnPostRewardsError, FOnPostRewardsComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPostRewardsRequest, URewardsResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostRewardsRequest*, FOnPostRewardsSuccess, FOnPostRewardsError, FOnPostRewardsComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPostRewardsRequest*, TBeamFullResponseHandler<UPostRewardsRequest*, URewardsResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostRewardsRequest*,
                                                                                   TBeamFullResponseHandler<UPostRewardsRequest*, URewardsResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UGetGlobalRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UGetGlobalRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UGetGlobalRequest, UGetStandingsResponse>(
	const int64&, UGetGlobalRequest*, FOnGetGlobalSuccess, FOnGetGlobalError, FOnGetGlobalComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UGetGlobalRequest, UGetStandingsResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetGlobalRequest*, FOnGetGlobalSuccess, FOnGetGlobalError, FOnGetGlobalComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UGetGlobalRequest*, TBeamFullResponseHandler<UGetGlobalRequest*, UGetStandingsResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetGlobalRequest*,
                                                                                   TBeamFullResponseHandler<UGetGlobalRequest*, UGetStandingsResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UGetStandingsGroupRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UGetStandingsGroupRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UGetStandingsGroupRequest, UGetStandingsResponse>(
	const int64&, UGetStandingsGroupRequest*, FOnGetStandingsGroupSuccess, FOnGetStandingsGroupError, FOnGetStandingsGroupComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UGetStandingsGroupRequest, UGetStandingsResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetStandingsGroupRequest*, FOnGetStandingsGroupSuccess, FOnGetStandingsGroupError, FOnGetStandingsGroupComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UGetStandingsGroupRequest*, TBeamFullResponseHandler<UGetStandingsGroupRequest*, UGetStandingsResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetStandingsGroupRequest*,
                                                                                   TBeamFullResponseHandler<UGetStandingsGroupRequest*, UGetStandingsResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UGetStandingsRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UGetStandingsRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UGetStandingsRequest, UGetStandingsResponse>(
	const int64&, UGetStandingsRequest*, FOnGetStandingsSuccess, FOnGetStandingsError, FOnGetStandingsComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UGetStandingsRequest, UGetStandingsResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetStandingsRequest*, FOnGetStandingsSuccess, FOnGetStandingsError, FOnGetStandingsComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UGetStandingsRequest*, TBeamFullResponseHandler<UGetStandingsRequest*, UGetStandingsResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetStandingsRequest*,
                                                                                   TBeamFullResponseHandler<UGetStandingsRequest*, UGetStandingsResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UGetAdminPlayerRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UGetAdminPlayerRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UGetAdminPlayerRequest, UAdminGetPlayerStatusResponse>(
	const int64&, UGetAdminPlayerRequest*, FOnGetAdminPlayerSuccess, FOnGetAdminPlayerError, FOnGetAdminPlayerComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UGetAdminPlayerRequest, UAdminGetPlayerStatusResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetAdminPlayerRequest*, FOnGetAdminPlayerSuccess, FOnGetAdminPlayerError, FOnGetAdminPlayerComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UGetAdminPlayerRequest*, TBeamFullResponseHandler<UGetAdminPlayerRequest*, UAdminGetPlayerStatusResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetAdminPlayerRequest*,
                                                                                   TBeamFullResponseHandler<UGetAdminPlayerRequest*, UAdminGetPlayerStatusResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPutAdminPlayerRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPutAdminPlayerRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPutAdminPlayerRequest, UAdminPlayerStatus>(
	const int64&, UPutAdminPlayerRequest*, FOnPutAdminPlayerSuccess, FOnPutAdminPlayerError, FOnPutAdminPlayerComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPutAdminPlayerRequest, UAdminPlayerStatus>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPutAdminPlayerRequest*, FOnPutAdminPlayerSuccess, FOnPutAdminPlayerError, FOnPutAdminPlayerComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPutAdminPlayerRequest*, TBeamFullResponseHandler<UPutAdminPlayerRequest*, UAdminPlayerStatus*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPutAdminPlayerRequest*,
                                                                                   TBeamFullResponseHandler<UPutAdminPlayerRequest*, UAdminPlayerStatus*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UBasicTournamentsGetMeRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UBasicTournamentsGetMeRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UBasicTournamentsGetMeRequest, UGetPlayerStatusResponse>(
	const int64&, UBasicTournamentsGetMeRequest*, FOnBasicTournamentsGetMeSuccess, FOnBasicTournamentsGetMeError, FOnBasicTournamentsGetMeComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UBasicTournamentsGetMeRequest, UGetPlayerStatusResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UBasicTournamentsGetMeRequest*, FOnBasicTournamentsGetMeSuccess, FOnBasicTournamentsGetMeError, FOnBasicTournamentsGetMeComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UBasicTournamentsGetMeRequest*, TBeamFullResponseHandler<UBasicTournamentsGetMeRequest*, UGetPlayerStatusResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UBasicTournamentsGetMeRequest*,
                                                                                   TBeamFullResponseHandler<UBasicTournamentsGetMeRequest*, UGetPlayerStatusResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UGetChampionsRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UGetChampionsRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UGetChampionsRequest, UGetChampionsResponse>(
	const int64&, UGetChampionsRequest*, FOnGetChampionsSuccess, FOnGetChampionsError, FOnGetChampionsComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UGetChampionsRequest, UGetChampionsResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetChampionsRequest*, FOnGetChampionsSuccess, FOnGetChampionsError, FOnGetChampionsComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UGetChampionsRequest*, TBeamFullResponseHandler<UGetChampionsRequest*, UGetChampionsResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetChampionsRequest*,
                                                                                   TBeamFullResponseHandler<UGetChampionsRequest*, UGetChampionsResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UBasicTournamentsGetGroupsRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UBasicTournamentsGetGroupsRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UBasicTournamentsGetGroupsRequest, UGetGroupsResponse>(
	const int64&, UBasicTournamentsGetGroupsRequest*, FOnBasicTournamentsGetGroupsSuccess, FOnBasicTournamentsGetGroupsError, FOnBasicTournamentsGetGroupsComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UBasicTournamentsGetGroupsRequest, UGetGroupsResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UBasicTournamentsGetGroupsRequest*, FOnBasicTournamentsGetGroupsSuccess, FOnBasicTournamentsGetGroupsError, FOnBasicTournamentsGetGroupsComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UBasicTournamentsGetGroupsRequest*, TBeamFullResponseHandler<UBasicTournamentsGetGroupsRequest*, UGetGroupsResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UBasicTournamentsGetGroupsRequest*,
                                                                                   TBeamFullResponseHandler<UBasicTournamentsGetGroupsRequest*, UGetGroupsResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UGetTokenRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UGetTokenRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UGetTokenRequest, UToken>(
	const int64&, UGetTokenRequest*, FOnGetTokenSuccess, FOnGetTokenError, FOnGetTokenComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UGetTokenRequest, UToken>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetTokenRequest*, FOnGetTokenSuccess, FOnGetTokenError, FOnGetTokenComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UGetTokenRequest*, TBeamFullResponseHandler<UGetTokenRequest*, UToken*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetTokenRequest*,
                                                                                   TBeamFullResponseHandler<UGetTokenRequest*, UToken*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UAuthenticateRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UAuthenticateRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UAuthenticateRequest, UTokenResponse>(
	const int64&, UAuthenticateRequest*, FOnAuthenticateSuccess, FOnAuthenticateError, FOnAuthenticateComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UAuthenticateRequest, UTokenResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UAuthenticateRequest*, FOnAuthenticateSuccess, FOnAuthenticateError, FOnAuthenticateComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UAuthenticateRequest*, TBeamFullResponseHandler<UAuthenticateRequest*, UTokenResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UAuthenticateRequest*,
                                                                                   TBeamFullResponseHandler<UAuthenticateRequest*, UTokenResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UGetTokenListRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UGetTokenListRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UGetTokenListRequest, UListTokenResponse>(
	const int64&, UGetTokenListRequest*, FOnGetTokenListSuccess, FOnGetTokenListError, FOnGetTokenListComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UGetTokenListRequest, UListTokenResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetTokenListRequest*, FOnGetTokenListSuccess, FOnGetTokenListError, FOnGetTokenListComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UGetTokenListRequest*, TBeamFullResponseHandler<UGetTokenListRequest*, UListTokenResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetTokenListRequest*,
                                                                                   TBeamFullResponseHandler<UGetTokenListRequest*, UListTokenResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPutTokenRevokeRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPutTokenRevokeRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPutTokenRevokeRequest, UCommonResponse>(
	const int64&, UPutTokenRevokeRequest*, FOnPutTokenRevokeSuccess, FOnPutTokenRevokeError, FOnPutTokenRevokeComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPutTokenRevokeRequest, UCommonResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPutTokenRevokeRequest*, FOnPutTokenRevokeSuccess, FOnPutTokenRevokeError, FOnPutTokenRevokeComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPutTokenRevokeRequest*, TBeamFullResponseHandler<UPutTokenRevokeRequest*, UCommonResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPutTokenRevokeRequest*,
                                                                                   TBeamFullResponseHandler<UPutTokenRevokeRequest*, UCommonResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UGetCloudsavingRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UGetCloudsavingRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UGetCloudsavingRequest, UManifest>(
	const int64&, UGetCloudsavingRequest*, FOnGetCloudsavingSuccess, FOnGetCloudsavingError, FOnGetCloudsavingComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UGetCloudsavingRequest, UManifest>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetCloudsavingRequest*, FOnGetCloudsavingSuccess, FOnGetCloudsavingError, FOnGetCloudsavingComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UGetCloudsavingRequest*, TBeamFullResponseHandler<UGetCloudsavingRequest*, UManifest*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetCloudsavingRequest*,
                                                                                   TBeamFullResponseHandler<UGetCloudsavingRequest*, UManifest*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPostDataReplaceRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPostDataReplaceRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPostDataReplaceRequest, UManifest>(
	const int64&, UPostDataReplaceRequest*, FOnPostDataReplaceSuccess, FOnPostDataReplaceError, FOnPostDataReplaceComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPostDataReplaceRequest, UManifest>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostDataReplaceRequest*, FOnPostDataReplaceSuccess, FOnPostDataReplaceError, FOnPostDataReplaceComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPostDataReplaceRequest*, TBeamFullResponseHandler<UPostDataReplaceRequest*, UManifest*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostDataReplaceRequest*,
                                                                                   TBeamFullResponseHandler<UPostDataReplaceRequest*, UManifest*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UDeleteDataRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UDeleteDataRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UDeleteDataRequest, UEmptyResponse>(
	const int64&, UDeleteDataRequest*, FOnDeleteDataSuccess, FOnDeleteDataError, FOnDeleteDataComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UDeleteDataRequest, UEmptyResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UDeleteDataRequest*, FOnDeleteDataSuccess, FOnDeleteDataError, FOnDeleteDataComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UDeleteDataRequest*, TBeamFullResponseHandler<UDeleteDataRequest*, UEmptyResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UDeleteDataRequest*,
                                                                                   TBeamFullResponseHandler<UDeleteDataRequest*, UEmptyResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPostDataDownloadURLRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPostDataDownloadURLRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPostDataDownloadURLRequest, UURLSResponse>(
	const int64&, UPostDataDownloadURLRequest*, FOnPostDataDownloadURLSuccess, FOnPostDataDownloadURLError, FOnPostDataDownloadURLComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPostDataDownloadURLRequest, UURLSResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostDataDownloadURLRequest*, FOnPostDataDownloadURLSuccess, FOnPostDataDownloadURLError, FOnPostDataDownloadURLComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPostDataDownloadURLRequest*, TBeamFullResponseHandler<UPostDataDownloadURLRequest*, UURLSResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostDataDownloadURLRequest*,
                                                                                   TBeamFullResponseHandler<UPostDataDownloadURLRequest*, UURLSResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UGetDataMetadataRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UGetDataMetadataRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UGetDataMetadataRequest, UObjectsMetadataResponse>(
	const int64&, UGetDataMetadataRequest*, FOnGetDataMetadataSuccess, FOnGetDataMetadataError, FOnGetDataMetadataComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UGetDataMetadataRequest, UObjectsMetadataResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetDataMetadataRequest*, FOnGetDataMetadataSuccess, FOnGetDataMetadataError, FOnGetDataMetadataComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UGetDataMetadataRequest*, TBeamFullResponseHandler<UGetDataMetadataRequest*, UObjectsMetadataResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetDataMetadataRequest*,
                                                                                   TBeamFullResponseHandler<UGetDataMetadataRequest*, UObjectsMetadataResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPostDataDownloadURLFromPortalRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPostDataDownloadURLFromPortalRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPostDataDownloadURLFromPortalRequest, UURLSResponse>(
	const int64&, UPostDataDownloadURLFromPortalRequest*, FOnPostDataDownloadURLFromPortalSuccess, FOnPostDataDownloadURLFromPortalError, FOnPostDataDownloadURLFromPortalComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPostDataDownloadURLFromPortalRequest, UURLSResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostDataDownloadURLFromPortalRequest*, FOnPostDataDownloadURLFromPortalSuccess, FOnPostDataDownloadURLFromPortalError, FOnPostDataDownloadURLFromPortalComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPostDataDownloadURLFromPortalRequest*, TBeamFullResponseHandler<UPostDataDownloadURLFromPortalRequest*, UURLSResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostDataDownloadURLFromPortalRequest*,
                                                                                   TBeamFullResponseHandler<UPostDataDownloadURLFromPortalRequest*, UURLSResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPutDataMoveRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPutDataMoveRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPutDataMoveRequest, UManifest>(
	const int64&, UPutDataMoveRequest*, FOnPutDataMoveSuccess, FOnPutDataMoveError, FOnPutDataMoveComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPutDataMoveRequest, UManifest>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPutDataMoveRequest*, FOnPutDataMoveSuccess, FOnPutDataMoveError, FOnPutDataMoveComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPutDataMoveRequest*, TBeamFullResponseHandler<UPutDataMoveRequest*, UManifest*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPutDataMoveRequest*,
                                                                                   TBeamFullResponseHandler<UPutDataMoveRequest*, UManifest*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPutDataMoveFromPortalRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPutDataMoveFromPortalRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPutDataMoveFromPortalRequest, UManifest>(
	const int64&, UPutDataMoveFromPortalRequest*, FOnPutDataMoveFromPortalSuccess, FOnPutDataMoveFromPortalError, FOnPutDataMoveFromPortalComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPutDataMoveFromPortalRequest, UManifest>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPutDataMoveFromPortalRequest*, FOnPutDataMoveFromPortalSuccess, FOnPutDataMoveFromPortalError, FOnPutDataMoveFromPortalComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPutDataMoveFromPortalRequest*, TBeamFullResponseHandler<UPutDataMoveFromPortalRequest*, UManifest*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPutDataMoveFromPortalRequest*,
                                                                                   TBeamFullResponseHandler<UPutDataMoveFromPortalRequest*, UManifest*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPostDataUploadURLFromPortalRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPostDataUploadURLFromPortalRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPostDataUploadURLFromPortalRequest, UURLSResponse>(
	const int64&, UPostDataUploadURLFromPortalRequest*, FOnPostDataUploadURLFromPortalSuccess, FOnPostDataUploadURLFromPortalError, FOnPostDataUploadURLFromPortalComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPostDataUploadURLFromPortalRequest, UURLSResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostDataUploadURLFromPortalRequest*, FOnPostDataUploadURLFromPortalSuccess, FOnPostDataUploadURLFromPortalError, FOnPostDataUploadURLFromPortalComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPostDataUploadURLFromPortalRequest*, TBeamFullResponseHandler<UPostDataUploadURLFromPortalRequest*, UURLSResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostDataUploadURLFromPortalRequest*,
                                                                                   TBeamFullResponseHandler<UPostDataUploadURLFromPortalRequest*, UURLSResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPutDataCommitManifestRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPutDataCommitManifestRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPutDataCommitManifestRequest, UManifest>(
	const int64&, UPutDataCommitManifestRequest*, FOnPutDataCommitManifestSuccess, FOnPutDataCommitManifestError, FOnPutDataCommitManifestComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPutDataCommitManifestRequest, UManifest>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPutDataCommitManifestRequest*, FOnPutDataCommitManifestSuccess, FOnPutDataCommitManifestError, FOnPutDataCommitManifestComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPutDataCommitManifestRequest*, TBeamFullResponseHandler<UPutDataCommitManifestRequest*, UManifest*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPutDataCommitManifestRequest*,
                                                                                   TBeamFullResponseHandler<UPutDataCommitManifestRequest*, UManifest*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPostDataUploadURLRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPostDataUploadURLRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPostDataUploadURLRequest, UURLSResponse>(
	const int64&, UPostDataUploadURLRequest*, FOnPostDataUploadURLSuccess, FOnPostDataUploadURLError, FOnPostDataUploadURLComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPostDataUploadURLRequest, UURLSResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostDataUploadURLRequest*, FOnPostDataUploadURLSuccess, FOnPostDataUploadURLError, FOnPostDataUploadURLComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPostDataUploadURLRequest*, TBeamFullResponseHandler<UPostDataUploadURLRequest*, UURLSResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostDataUploadURLRequest*,
                                                                                   TBeamFullResponseHandler<UPostDataUploadURLRequest*, UURLSResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPostWindowsPurchaseTrackRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPostWindowsPurchaseTrackRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPostWindowsPurchaseTrackRequest, UPaymentResultResponse>(
	const int64&, UPostWindowsPurchaseTrackRequest*, FOnPostWindowsPurchaseTrackSuccess, FOnPostWindowsPurchaseTrackError, FOnPostWindowsPurchaseTrackComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPostWindowsPurchaseTrackRequest, UPaymentResultResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostWindowsPurchaseTrackRequest*, FOnPostWindowsPurchaseTrackSuccess, FOnPostWindowsPurchaseTrackError, FOnPostWindowsPurchaseTrackComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPostWindowsPurchaseTrackRequest*, TBeamFullResponseHandler<UPostWindowsPurchaseTrackRequest*, UPaymentResultResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostWindowsPurchaseTrackRequest*,
                                                                                   TBeamFullResponseHandler<UPostWindowsPurchaseTrackRequest*, UPaymentResultResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UGetAuditsRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UGetAuditsRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UGetAuditsRequest, UListAuditResponse>(
	const int64&, UGetAuditsRequest*, FOnGetAuditsSuccess, FOnGetAuditsError, FOnGetAuditsComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UGetAuditsRequest, UListAuditResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetAuditsRequest*, FOnGetAuditsSuccess, FOnGetAuditsError, FOnGetAuditsComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UGetAuditsRequest*, TBeamFullResponseHandler<UGetAuditsRequest*, UListAuditResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetAuditsRequest*,
                                                                                   TBeamFullResponseHandler<UGetAuditsRequest*, UListAuditResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPostWindowsPurchaseCompleteRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPostWindowsPurchaseCompleteRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPostWindowsPurchaseCompleteRequest, UPaymentResultResponse>(
	const int64&, UPostWindowsPurchaseCompleteRequest*, FOnPostWindowsPurchaseCompleteSuccess, FOnPostWindowsPurchaseCompleteError, FOnPostWindowsPurchaseCompleteComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPostWindowsPurchaseCompleteRequest, UPaymentResultResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostWindowsPurchaseCompleteRequest*, FOnPostWindowsPurchaseCompleteSuccess, FOnPostWindowsPurchaseCompleteError, FOnPostWindowsPurchaseCompleteComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPostWindowsPurchaseCompleteRequest*, TBeamFullResponseHandler<UPostWindowsPurchaseCompleteRequest*, UPaymentResultResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostWindowsPurchaseCompleteRequest*,
                                                                                   TBeamFullResponseHandler<UPostWindowsPurchaseCompleteRequest*, UPaymentResultResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UGetFacebookUpdateRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UGetFacebookUpdateRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UGetFacebookUpdateRequest, USubscriptionVerificationResponse>(
	const int64&, UGetFacebookUpdateRequest*, FOnGetFacebookUpdateSuccess, FOnGetFacebookUpdateError, FOnGetFacebookUpdateComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UGetFacebookUpdateRequest, USubscriptionVerificationResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetFacebookUpdateRequest*, FOnGetFacebookUpdateSuccess, FOnGetFacebookUpdateError, FOnGetFacebookUpdateComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UGetFacebookUpdateRequest*, TBeamFullResponseHandler<UGetFacebookUpdateRequest*, USubscriptionVerificationResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetFacebookUpdateRequest*,
                                                                                   TBeamFullResponseHandler<UGetFacebookUpdateRequest*, USubscriptionVerificationResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPostFacebookUpdateRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPostFacebookUpdateRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPostFacebookUpdateRequest, UFacebookPaymentUpdateResponse>(
	const int64&, UPostFacebookUpdateRequest*, FOnPostFacebookUpdateSuccess, FOnPostFacebookUpdateError, FOnPostFacebookUpdateComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPostFacebookUpdateRequest, UFacebookPaymentUpdateResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostFacebookUpdateRequest*, FOnPostFacebookUpdateSuccess, FOnPostFacebookUpdateError, FOnPostFacebookUpdateComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPostFacebookUpdateRequest*, TBeamFullResponseHandler<UPostFacebookUpdateRequest*, UFacebookPaymentUpdateResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostFacebookUpdateRequest*,
                                                                                   TBeamFullResponseHandler<UPostFacebookUpdateRequest*, UFacebookPaymentUpdateResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPostFacebookPurchaseCompleteRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPostFacebookPurchaseCompleteRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPostFacebookPurchaseCompleteRequest, UPaymentResultResponse>(
	const int64&, UPostFacebookPurchaseCompleteRequest*, FOnPostFacebookPurchaseCompleteSuccess, FOnPostFacebookPurchaseCompleteError, FOnPostFacebookPurchaseCompleteComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPostFacebookPurchaseCompleteRequest, UPaymentResultResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostFacebookPurchaseCompleteRequest*, FOnPostFacebookPurchaseCompleteSuccess, FOnPostFacebookPurchaseCompleteError, FOnPostFacebookPurchaseCompleteComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPostFacebookPurchaseCompleteRequest*, TBeamFullResponseHandler<UPostFacebookPurchaseCompleteRequest*, UPaymentResultResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostFacebookPurchaseCompleteRequest*,
                                                                                   TBeamFullResponseHandler<UPostFacebookPurchaseCompleteRequest*, UPaymentResultResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPostTestPurchaseCompleteRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPostTestPurchaseCompleteRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPostTestPurchaseCompleteRequest, UPaymentResultResponse>(
	const int64&, UPostTestPurchaseCompleteRequest*, FOnPostTestPurchaseCompleteSuccess, FOnPostTestPurchaseCompleteError, FOnPostTestPurchaseCompleteComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPostTestPurchaseCompleteRequest, UPaymentResultResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostTestPurchaseCompleteRequest*, FOnPostTestPurchaseCompleteSuccess, FOnPostTestPurchaseCompleteError, FOnPostTestPurchaseCompleteComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPostTestPurchaseCompleteRequest*, TBeamFullResponseHandler<UPostTestPurchaseCompleteRequest*, UPaymentResultResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostTestPurchaseCompleteRequest*,
                                                                                   TBeamFullResponseHandler<UPostTestPurchaseCompleteRequest*, UPaymentResultResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UGetItunesProductRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UGetItunesProductRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UGetItunesProductRequest, UGetProductResponse>(
	const int64&, UGetItunesProductRequest*, FOnGetItunesProductSuccess, FOnGetItunesProductError, FOnGetItunesProductComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UGetItunesProductRequest, UGetProductResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetItunesProductRequest*, FOnGetItunesProductSuccess, FOnGetItunesProductError, FOnGetItunesProductComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UGetItunesProductRequest*, TBeamFullResponseHandler<UGetItunesProductRequest*, UGetProductResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetItunesProductRequest*,
                                                                                   TBeamFullResponseHandler<UGetItunesProductRequest*, UGetProductResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPostGoogleplayPurchaseCompleteRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPostGoogleplayPurchaseCompleteRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPostGoogleplayPurchaseCompleteRequest, UPaymentResultResponse>(
	const int64&, UPostGoogleplayPurchaseCompleteRequest*, FOnPostGoogleplayPurchaseCompleteSuccess, FOnPostGoogleplayPurchaseCompleteError, FOnPostGoogleplayPurchaseCompleteComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPostGoogleplayPurchaseCompleteRequest, UPaymentResultResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostGoogleplayPurchaseCompleteRequest*, FOnPostGoogleplayPurchaseCompleteSuccess, FOnPostGoogleplayPurchaseCompleteError, FOnPostGoogleplayPurchaseCompleteComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPostGoogleplayPurchaseCompleteRequest*, TBeamFullResponseHandler<UPostGoogleplayPurchaseCompleteRequest*, UPaymentResultResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostGoogleplayPurchaseCompleteRequest*,
                                                                                   TBeamFullResponseHandler<UPostGoogleplayPurchaseCompleteRequest*, UPaymentResultResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPostTestPurchaseTrackRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPostTestPurchaseTrackRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPostTestPurchaseTrackRequest, UPaymentResultResponse>(
	const int64&, UPostTestPurchaseTrackRequest*, FOnPostTestPurchaseTrackSuccess, FOnPostTestPurchaseTrackError, FOnPostTestPurchaseTrackComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPostTestPurchaseTrackRequest, UPaymentResultResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostTestPurchaseTrackRequest*, FOnPostTestPurchaseTrackSuccess, FOnPostTestPurchaseTrackError, FOnPostTestPurchaseTrackComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPostTestPurchaseTrackRequest*, TBeamFullResponseHandler<UPostTestPurchaseTrackRequest*, UPaymentResultResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostTestPurchaseTrackRequest*,
                                                                                   TBeamFullResponseHandler<UPostTestPurchaseTrackRequest*, UPaymentResultResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPostGoogleplayPurchaseVerifyRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPostGoogleplayPurchaseVerifyRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPostGoogleplayPurchaseVerifyRequest, UPaymentResultResponse>(
	const int64&, UPostGoogleplayPurchaseVerifyRequest*, FOnPostGoogleplayPurchaseVerifySuccess, FOnPostGoogleplayPurchaseVerifyError, FOnPostGoogleplayPurchaseVerifyComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPostGoogleplayPurchaseVerifyRequest, UPaymentResultResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostGoogleplayPurchaseVerifyRequest*, FOnPostGoogleplayPurchaseVerifySuccess, FOnPostGoogleplayPurchaseVerifyError, FOnPostGoogleplayPurchaseVerifyComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPostGoogleplayPurchaseVerifyRequest*, TBeamFullResponseHandler<UPostGoogleplayPurchaseVerifyRequest*, UPaymentResultResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostGoogleplayPurchaseVerifyRequest*,
                                                                                   TBeamFullResponseHandler<UPostGoogleplayPurchaseVerifyRequest*, UPaymentResultResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPostCouponPurchaseTrackRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPostCouponPurchaseTrackRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPostCouponPurchaseTrackRequest, UPaymentResultResponse>(
	const int64&, UPostCouponPurchaseTrackRequest*, FOnPostCouponPurchaseTrackSuccess, FOnPostCouponPurchaseTrackError, FOnPostCouponPurchaseTrackComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPostCouponPurchaseTrackRequest, UPaymentResultResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostCouponPurchaseTrackRequest*, FOnPostCouponPurchaseTrackSuccess, FOnPostCouponPurchaseTrackError, FOnPostCouponPurchaseTrackComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPostCouponPurchaseTrackRequest*, TBeamFullResponseHandler<UPostCouponPurchaseTrackRequest*, UPaymentResultResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostCouponPurchaseTrackRequest*,
                                                                                   TBeamFullResponseHandler<UPostCouponPurchaseTrackRequest*, UPaymentResultResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPostSteamPurchaseCompleteRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPostSteamPurchaseCompleteRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPostSteamPurchaseCompleteRequest, UPaymentResultResponse>(
	const int64&, UPostSteamPurchaseCompleteRequest*, FOnPostSteamPurchaseCompleteSuccess, FOnPostSteamPurchaseCompleteError, FOnPostSteamPurchaseCompleteComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPostSteamPurchaseCompleteRequest, UPaymentResultResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostSteamPurchaseCompleteRequest*, FOnPostSteamPurchaseCompleteSuccess, FOnPostSteamPurchaseCompleteError, FOnPostSteamPurchaseCompleteComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPostSteamPurchaseCompleteRequest*, TBeamFullResponseHandler<UPostSteamPurchaseCompleteRequest*, UPaymentResultResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostSteamPurchaseCompleteRequest*,
                                                                                   TBeamFullResponseHandler<UPostSteamPurchaseCompleteRequest*, UPaymentResultResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPostFacebookPurchaseTrackRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPostFacebookPurchaseTrackRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPostFacebookPurchaseTrackRequest, UPaymentResultResponse>(
	const int64&, UPostFacebookPurchaseTrackRequest*, FOnPostFacebookPurchaseTrackSuccess, FOnPostFacebookPurchaseTrackError, FOnPostFacebookPurchaseTrackComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPostFacebookPurchaseTrackRequest, UPaymentResultResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostFacebookPurchaseTrackRequest*, FOnPostFacebookPurchaseTrackSuccess, FOnPostFacebookPurchaseTrackError, FOnPostFacebookPurchaseTrackComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPostFacebookPurchaseTrackRequest*, TBeamFullResponseHandler<UPostFacebookPurchaseTrackRequest*, UPaymentResultResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostFacebookPurchaseTrackRequest*,
                                                                                   TBeamFullResponseHandler<UPostFacebookPurchaseTrackRequest*, UPaymentResultResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPostTestPurchaseVerifyRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPostTestPurchaseVerifyRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPostTestPurchaseVerifyRequest, UPaymentResultResponse>(
	const int64&, UPostTestPurchaseVerifyRequest*, FOnPostTestPurchaseVerifySuccess, FOnPostTestPurchaseVerifyError, FOnPostTestPurchaseVerifyComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPostTestPurchaseVerifyRequest, UPaymentResultResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostTestPurchaseVerifyRequest*, FOnPostTestPurchaseVerifySuccess, FOnPostTestPurchaseVerifyError, FOnPostTestPurchaseVerifyComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPostTestPurchaseVerifyRequest*, TBeamFullResponseHandler<UPostTestPurchaseVerifyRequest*, UPaymentResultResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostTestPurchaseVerifyRequest*,
                                                                                   TBeamFullResponseHandler<UPostTestPurchaseVerifyRequest*, UPaymentResultResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPostGoogleplayPurchaseTrackRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPostGoogleplayPurchaseTrackRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPostGoogleplayPurchaseTrackRequest, UPaymentResultResponse>(
	const int64&, UPostGoogleplayPurchaseTrackRequest*, FOnPostGoogleplayPurchaseTrackSuccess, FOnPostGoogleplayPurchaseTrackError, FOnPostGoogleplayPurchaseTrackComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPostGoogleplayPurchaseTrackRequest, UPaymentResultResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostGoogleplayPurchaseTrackRequest*, FOnPostGoogleplayPurchaseTrackSuccess, FOnPostGoogleplayPurchaseTrackError, FOnPostGoogleplayPurchaseTrackComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPostGoogleplayPurchaseTrackRequest*, TBeamFullResponseHandler<UPostGoogleplayPurchaseTrackRequest*, UPaymentResultResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostGoogleplayPurchaseTrackRequest*,
                                                                                   TBeamFullResponseHandler<UPostGoogleplayPurchaseTrackRequest*, UPaymentResultResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UGetSteamPricesRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UGetSteamPricesRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UGetSteamPricesRequest, ULocalizedPriceMap>(
	const int64&, UGetSteamPricesRequest*, FOnGetSteamPricesSuccess, FOnGetSteamPricesError, FOnGetSteamPricesComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UGetSteamPricesRequest, ULocalizedPriceMap>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetSteamPricesRequest*, FOnGetSteamPricesSuccess, FOnGetSteamPricesError, FOnGetSteamPricesComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UGetSteamPricesRequest*, TBeamFullResponseHandler<UGetSteamPricesRequest*, ULocalizedPriceMap*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetSteamPricesRequest*,
                                                                                   TBeamFullResponseHandler<UGetSteamPricesRequest*, ULocalizedPriceMap*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPostWindowsPurchaseVerifyRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPostWindowsPurchaseVerifyRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPostWindowsPurchaseVerifyRequest, UPaymentResultResponse>(
	const int64&, UPostWindowsPurchaseVerifyRequest*, FOnPostWindowsPurchaseVerifySuccess, FOnPostWindowsPurchaseVerifyError, FOnPostWindowsPurchaseVerifyComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPostWindowsPurchaseVerifyRequest, UPaymentResultResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostWindowsPurchaseVerifyRequest*, FOnPostWindowsPurchaseVerifySuccess, FOnPostWindowsPurchaseVerifyError, FOnPostWindowsPurchaseVerifyComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPostWindowsPurchaseVerifyRequest*, TBeamFullResponseHandler<UPostWindowsPurchaseVerifyRequest*, UPaymentResultResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostWindowsPurchaseVerifyRequest*,
                                                                                   TBeamFullResponseHandler<UPostWindowsPurchaseVerifyRequest*, UPaymentResultResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPostItunesPurchaseVerifyRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPostItunesPurchaseVerifyRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPostItunesPurchaseVerifyRequest, UPaymentResultResponse>(
	const int64&, UPostItunesPurchaseVerifyRequest*, FOnPostItunesPurchaseVerifySuccess, FOnPostItunesPurchaseVerifyError, FOnPostItunesPurchaseVerifyComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPostItunesPurchaseVerifyRequest, UPaymentResultResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostItunesPurchaseVerifyRequest*, FOnPostItunesPurchaseVerifySuccess, FOnPostItunesPurchaseVerifyError, FOnPostItunesPurchaseVerifyComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPostItunesPurchaseVerifyRequest*, TBeamFullResponseHandler<UPostItunesPurchaseVerifyRequest*, UPaymentResultResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostItunesPurchaseVerifyRequest*,
                                                                                   TBeamFullResponseHandler<UPostItunesPurchaseVerifyRequest*, UPaymentResultResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPostItunesPurchaseCompleteRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPostItunesPurchaseCompleteRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPostItunesPurchaseCompleteRequest, UPaymentResultResponse>(
	const int64&, UPostItunesPurchaseCompleteRequest*, FOnPostItunesPurchaseCompleteSuccess, FOnPostItunesPurchaseCompleteError, FOnPostItunesPurchaseCompleteComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPostItunesPurchaseCompleteRequest, UPaymentResultResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostItunesPurchaseCompleteRequest*, FOnPostItunesPurchaseCompleteSuccess, FOnPostItunesPurchaseCompleteError, FOnPostItunesPurchaseCompleteComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPostItunesPurchaseCompleteRequest*, TBeamFullResponseHandler<UPostItunesPurchaseCompleteRequest*, UPaymentResultResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostItunesPurchaseCompleteRequest*,
                                                                                   TBeamFullResponseHandler<UPostItunesPurchaseCompleteRequest*, UPaymentResultResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPostFacebookPurchaseVerifyRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPostFacebookPurchaseVerifyRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPostFacebookPurchaseVerifyRequest, UPaymentResultResponse>(
	const int64&, UPostFacebookPurchaseVerifyRequest*, FOnPostFacebookPurchaseVerifySuccess, FOnPostFacebookPurchaseVerifyError, FOnPostFacebookPurchaseVerifyComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPostFacebookPurchaseVerifyRequest, UPaymentResultResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostFacebookPurchaseVerifyRequest*, FOnPostFacebookPurchaseVerifySuccess, FOnPostFacebookPurchaseVerifyError, FOnPostFacebookPurchaseVerifyComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPostFacebookPurchaseVerifyRequest*, TBeamFullResponseHandler<UPostFacebookPurchaseVerifyRequest*, UPaymentResultResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostFacebookPurchaseVerifyRequest*,
                                                                                   TBeamFullResponseHandler<UPostFacebookPurchaseVerifyRequest*, UPaymentResultResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPostSteamPurchaseTrackRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPostSteamPurchaseTrackRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPostSteamPurchaseTrackRequest, UPaymentResultResponse>(
	const int64&, UPostSteamPurchaseTrackRequest*, FOnPostSteamPurchaseTrackSuccess, FOnPostSteamPurchaseTrackError, FOnPostSteamPurchaseTrackComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPostSteamPurchaseTrackRequest, UPaymentResultResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostSteamPurchaseTrackRequest*, FOnPostSteamPurchaseTrackSuccess, FOnPostSteamPurchaseTrackError, FOnPostSteamPurchaseTrackComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPostSteamPurchaseTrackRequest*, TBeamFullResponseHandler<UPostSteamPurchaseTrackRequest*, UPaymentResultResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostSteamPurchaseTrackRequest*,
                                                                                   TBeamFullResponseHandler<UPostSteamPurchaseTrackRequest*, UPaymentResultResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPostCouponPurchaseVerifyRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPostCouponPurchaseVerifyRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPostCouponPurchaseVerifyRequest, UPaymentResultResponse>(
	const int64&, UPostCouponPurchaseVerifyRequest*, FOnPostCouponPurchaseVerifySuccess, FOnPostCouponPurchaseVerifyError, FOnPostCouponPurchaseVerifyComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPostCouponPurchaseVerifyRequest, UPaymentResultResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostCouponPurchaseVerifyRequest*, FOnPostCouponPurchaseVerifySuccess, FOnPostCouponPurchaseVerifyError, FOnPostCouponPurchaseVerifyComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPostCouponPurchaseVerifyRequest*, TBeamFullResponseHandler<UPostCouponPurchaseVerifyRequest*, UPaymentResultResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostCouponPurchaseVerifyRequest*,
                                                                                   TBeamFullResponseHandler<UPostCouponPurchaseVerifyRequest*, UPaymentResultResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UGetWindowsProductRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UGetWindowsProductRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UGetWindowsProductRequest, UGetProductResponse>(
	const int64&, UGetWindowsProductRequest*, FOnGetWindowsProductSuccess, FOnGetWindowsProductError, FOnGetWindowsProductComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UGetWindowsProductRequest, UGetProductResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetWindowsProductRequest*, FOnGetWindowsProductSuccess, FOnGetWindowsProductError, FOnGetWindowsProductComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UGetWindowsProductRequest*, TBeamFullResponseHandler<UGetWindowsProductRequest*, UGetProductResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetWindowsProductRequest*,
                                                                                   TBeamFullResponseHandler<UGetWindowsProductRequest*, UGetProductResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UGetFacebookProductRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UGetFacebookProductRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UGetFacebookProductRequest, UGetProductResponse>(
	const int64&, UGetFacebookProductRequest*, FOnGetFacebookProductSuccess, FOnGetFacebookProductError, FOnGetFacebookProductComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UGetFacebookProductRequest, UGetProductResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetFacebookProductRequest*, FOnGetFacebookProductSuccess, FOnGetFacebookProductError, FOnGetFacebookProductComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UGetFacebookProductRequest*, TBeamFullResponseHandler<UGetFacebookProductRequest*, UGetProductResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetFacebookProductRequest*,
                                                                                   TBeamFullResponseHandler<UGetFacebookProductRequest*, UGetProductResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UGetCouponProductRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UGetCouponProductRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UGetCouponProductRequest, UGetProductResponse>(
	const int64&, UGetCouponProductRequest*, FOnGetCouponProductSuccess, FOnGetCouponProductError, FOnGetCouponProductComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UGetCouponProductRequest, UGetProductResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetCouponProductRequest*, FOnGetCouponProductSuccess, FOnGetCouponProductError, FOnGetCouponProductComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UGetCouponProductRequest*, TBeamFullResponseHandler<UGetCouponProductRequest*, UGetProductResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetCouponProductRequest*,
                                                                                   TBeamFullResponseHandler<UGetCouponProductRequest*, UGetProductResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UGetSteamProductsRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UGetSteamProductsRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UGetSteamProductsRequest, UGetProductsResponse>(
	const int64&, UGetSteamProductsRequest*, FOnGetSteamProductsSuccess, FOnGetSteamProductsError, FOnGetSteamProductsComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UGetSteamProductsRequest, UGetProductsResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetSteamProductsRequest*, FOnGetSteamProductsSuccess, FOnGetSteamProductsError, FOnGetSteamProductsComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UGetSteamProductsRequest*, TBeamFullResponseHandler<UGetSteamProductsRequest*, UGetProductsResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetSteamProductsRequest*,
                                                                                   TBeamFullResponseHandler<UGetSteamProductsRequest*, UGetProductsResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPostSteamAuthRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPostSteamAuthRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPostSteamAuthRequest, UEmptyResponse>(
	const int64&, UPostSteamAuthRequest*, FOnPostSteamAuthSuccess, FOnPostSteamAuthError, FOnPostSteamAuthComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPostSteamAuthRequest, UEmptyResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostSteamAuthRequest*, FOnPostSteamAuthSuccess, FOnPostSteamAuthError, FOnPostSteamAuthComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPostSteamAuthRequest*, TBeamFullResponseHandler<UPostSteamAuthRequest*, UEmptyResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostSteamAuthRequest*,
                                                                                   TBeamFullResponseHandler<UPostSteamAuthRequest*, UEmptyResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UGetSteamProductRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UGetSteamProductRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UGetSteamProductRequest, UGetProductResponse>(
	const int64&, UGetSteamProductRequest*, FOnGetSteamProductSuccess, FOnGetSteamProductError, FOnGetSteamProductComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UGetSteamProductRequest, UGetProductResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetSteamProductRequest*, FOnGetSteamProductSuccess, FOnGetSteamProductError, FOnGetSteamProductComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UGetSteamProductRequest*, TBeamFullResponseHandler<UGetSteamProductRequest*, UGetProductResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetSteamProductRequest*,
                                                                                   TBeamFullResponseHandler<UGetSteamProductRequest*, UGetProductResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPostCouponPurchaseCompleteRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPostCouponPurchaseCompleteRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPostCouponPurchaseCompleteRequest, UPaymentResultResponse>(
	const int64&, UPostCouponPurchaseCompleteRequest*, FOnPostCouponPurchaseCompleteSuccess, FOnPostCouponPurchaseCompleteError, FOnPostCouponPurchaseCompleteComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPostCouponPurchaseCompleteRequest, UPaymentResultResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostCouponPurchaseCompleteRequest*, FOnPostCouponPurchaseCompleteSuccess, FOnPostCouponPurchaseCompleteError, FOnPostCouponPurchaseCompleteComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPostCouponPurchaseCompleteRequest*, TBeamFullResponseHandler<UPostCouponPurchaseCompleteRequest*, UPaymentResultResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostCouponPurchaseCompleteRequest*,
                                                                                   TBeamFullResponseHandler<UPostCouponPurchaseCompleteRequest*, UPaymentResultResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UGetGoogleplayProductRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UGetGoogleplayProductRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UGetGoogleplayProductRequest, UGetProductResponse>(
	const int64&, UGetGoogleplayProductRequest*, FOnGetGoogleplayProductSuccess, FOnGetGoogleplayProductError, FOnGetGoogleplayProductComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UGetGoogleplayProductRequest, UGetProductResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetGoogleplayProductRequest*, FOnGetGoogleplayProductSuccess, FOnGetGoogleplayProductError, FOnGetGoogleplayProductComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UGetGoogleplayProductRequest*, TBeamFullResponseHandler<UGetGoogleplayProductRequest*, UGetProductResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetGoogleplayProductRequest*,
                                                                                   TBeamFullResponseHandler<UGetGoogleplayProductRequest*, UGetProductResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UGetTestProductRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UGetTestProductRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UGetTestProductRequest, UGetProductResponse>(
	const int64&, UGetTestProductRequest*, FOnGetTestProductSuccess, FOnGetTestProductError, FOnGetTestProductComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UGetTestProductRequest, UGetProductResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetTestProductRequest*, FOnGetTestProductSuccess, FOnGetTestProductError, FOnGetTestProductComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UGetTestProductRequest*, TBeamFullResponseHandler<UGetTestProductRequest*, UGetProductResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetTestProductRequest*,
                                                                                   TBeamFullResponseHandler<UGetTestProductRequest*, UGetProductResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPostSteamPurchaseVerifyRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPostSteamPurchaseVerifyRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPostSteamPurchaseVerifyRequest, UPaymentResultResponse>(
	const int64&, UPostSteamPurchaseVerifyRequest*, FOnPostSteamPurchaseVerifySuccess, FOnPostSteamPurchaseVerifyError, FOnPostSteamPurchaseVerifyComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPostSteamPurchaseVerifyRequest, UPaymentResultResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostSteamPurchaseVerifyRequest*, FOnPostSteamPurchaseVerifySuccess, FOnPostSteamPurchaseVerifyError, FOnPostSteamPurchaseVerifyComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPostSteamPurchaseVerifyRequest*, TBeamFullResponseHandler<UPostSteamPurchaseVerifyRequest*, UPaymentResultResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostSteamPurchaseVerifyRequest*,
                                                                                   TBeamFullResponseHandler<UPostSteamPurchaseVerifyRequest*, UPaymentResultResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPostItunesPurchaseTrackRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPostItunesPurchaseTrackRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPostItunesPurchaseTrackRequest, UPaymentResultResponse>(
	const int64&, UPostItunesPurchaseTrackRequest*, FOnPostItunesPurchaseTrackSuccess, FOnPostItunesPurchaseTrackError, FOnPostItunesPurchaseTrackComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPostItunesPurchaseTrackRequest, UPaymentResultResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostItunesPurchaseTrackRequest*, FOnPostItunesPurchaseTrackSuccess, FOnPostItunesPurchaseTrackError, FOnPostItunesPurchaseTrackComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPostItunesPurchaseTrackRequest*, TBeamFullResponseHandler<UPostItunesPurchaseTrackRequest*, UPaymentResultResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostItunesPurchaseTrackRequest*,
                                                                                   TBeamFullResponseHandler<UPostItunesPurchaseTrackRequest*, UPaymentResultResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UGetPaymentsRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UGetPaymentsRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UGetPaymentsRequest, UCommonResponse>(
	const int64&, UGetPaymentsRequest*, FOnGetPaymentsSuccess, FOnGetPaymentsError, FOnGetPaymentsComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UGetPaymentsRequest, UCommonResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetPaymentsRequest*, FOnGetPaymentsSuccess, FOnGetPaymentsError, FOnGetPaymentsComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UGetPaymentsRequest*, TBeamFullResponseHandler<UGetPaymentsRequest*, UCommonResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetPaymentsRequest*,
                                                                                   TBeamFullResponseHandler<UGetPaymentsRequest*, UCommonResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPostTestPurchaseBeginRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPostTestPurchaseBeginRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPostTestPurchaseBeginRequest, UBeginPurchaseResponse>(
	const int64&, UPostTestPurchaseBeginRequest*, FOnPostTestPurchaseBeginSuccess, FOnPostTestPurchaseBeginError, FOnPostTestPurchaseBeginComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPostTestPurchaseBeginRequest, UBeginPurchaseResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostTestPurchaseBeginRequest*, FOnPostTestPurchaseBeginSuccess, FOnPostTestPurchaseBeginError, FOnPostTestPurchaseBeginComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPostTestPurchaseBeginRequest*, TBeamFullResponseHandler<UPostTestPurchaseBeginRequest*, UBeginPurchaseResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostTestPurchaseBeginRequest*,
                                                                                   TBeamFullResponseHandler<UPostTestPurchaseBeginRequest*, UBeginPurchaseResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPostSteamPurchaseFailRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPostSteamPurchaseFailRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPostSteamPurchaseFailRequest, UPaymentResultResponse>(
	const int64&, UPostSteamPurchaseFailRequest*, FOnPostSteamPurchaseFailSuccess, FOnPostSteamPurchaseFailError, FOnPostSteamPurchaseFailComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPostSteamPurchaseFailRequest, UPaymentResultResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostSteamPurchaseFailRequest*, FOnPostSteamPurchaseFailSuccess, FOnPostSteamPurchaseFailError, FOnPostSteamPurchaseFailComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPostSteamPurchaseFailRequest*, TBeamFullResponseHandler<UPostSteamPurchaseFailRequest*, UPaymentResultResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostSteamPurchaseFailRequest*,
                                                                                   TBeamFullResponseHandler<UPostSteamPurchaseFailRequest*, UPaymentResultResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPostFacebookPurchaseFailRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPostFacebookPurchaseFailRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPostFacebookPurchaseFailRequest, UPaymentResultResponse>(
	const int64&, UPostFacebookPurchaseFailRequest*, FOnPostFacebookPurchaseFailSuccess, FOnPostFacebookPurchaseFailError, FOnPostFacebookPurchaseFailComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPostFacebookPurchaseFailRequest, UPaymentResultResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostFacebookPurchaseFailRequest*, FOnPostFacebookPurchaseFailSuccess, FOnPostFacebookPurchaseFailError, FOnPostFacebookPurchaseFailComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPostFacebookPurchaseFailRequest*, TBeamFullResponseHandler<UPostFacebookPurchaseFailRequest*, UPaymentResultResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostFacebookPurchaseFailRequest*,
                                                                                   TBeamFullResponseHandler<UPostFacebookPurchaseFailRequest*, UPaymentResultResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPostGoogleplayPurchaseBeginRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPostGoogleplayPurchaseBeginRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPostGoogleplayPurchaseBeginRequest, UBeginPurchaseResponse>(
	const int64&, UPostGoogleplayPurchaseBeginRequest*, FOnPostGoogleplayPurchaseBeginSuccess, FOnPostGoogleplayPurchaseBeginError, FOnPostGoogleplayPurchaseBeginComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPostGoogleplayPurchaseBeginRequest, UBeginPurchaseResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostGoogleplayPurchaseBeginRequest*, FOnPostGoogleplayPurchaseBeginSuccess, FOnPostGoogleplayPurchaseBeginError, FOnPostGoogleplayPurchaseBeginComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPostGoogleplayPurchaseBeginRequest*, TBeamFullResponseHandler<UPostGoogleplayPurchaseBeginRequest*, UBeginPurchaseResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostGoogleplayPurchaseBeginRequest*,
                                                                                   TBeamFullResponseHandler<UPostGoogleplayPurchaseBeginRequest*, UBeginPurchaseResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPostItunesPurchaseBeginRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPostItunesPurchaseBeginRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPostItunesPurchaseBeginRequest, UBeginPurchaseResponse>(
	const int64&, UPostItunesPurchaseBeginRequest*, FOnPostItunesPurchaseBeginSuccess, FOnPostItunesPurchaseBeginError, FOnPostItunesPurchaseBeginComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPostItunesPurchaseBeginRequest, UBeginPurchaseResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostItunesPurchaseBeginRequest*, FOnPostItunesPurchaseBeginSuccess, FOnPostItunesPurchaseBeginError, FOnPostItunesPurchaseBeginComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPostItunesPurchaseBeginRequest*, TBeamFullResponseHandler<UPostItunesPurchaseBeginRequest*, UBeginPurchaseResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostItunesPurchaseBeginRequest*,
                                                                                   TBeamFullResponseHandler<UPostItunesPurchaseBeginRequest*, UBeginPurchaseResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPostFacebookPurchaseCancelRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPostFacebookPurchaseCancelRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPostFacebookPurchaseCancelRequest, UPaymentResultResponse>(
	const int64&, UPostFacebookPurchaseCancelRequest*, FOnPostFacebookPurchaseCancelSuccess, FOnPostFacebookPurchaseCancelError, FOnPostFacebookPurchaseCancelComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPostFacebookPurchaseCancelRequest, UPaymentResultResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostFacebookPurchaseCancelRequest*, FOnPostFacebookPurchaseCancelSuccess, FOnPostFacebookPurchaseCancelError, FOnPostFacebookPurchaseCancelComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPostFacebookPurchaseCancelRequest*, TBeamFullResponseHandler<UPostFacebookPurchaseCancelRequest*, UPaymentResultResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostFacebookPurchaseCancelRequest*,
                                                                                   TBeamFullResponseHandler<UPostFacebookPurchaseCancelRequest*, UPaymentResultResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPostItunesPurchaseFailRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPostItunesPurchaseFailRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPostItunesPurchaseFailRequest, UPaymentResultResponse>(
	const int64&, UPostItunesPurchaseFailRequest*, FOnPostItunesPurchaseFailSuccess, FOnPostItunesPurchaseFailError, FOnPostItunesPurchaseFailComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPostItunesPurchaseFailRequest, UPaymentResultResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostItunesPurchaseFailRequest*, FOnPostItunesPurchaseFailSuccess, FOnPostItunesPurchaseFailError, FOnPostItunesPurchaseFailComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPostItunesPurchaseFailRequest*, TBeamFullResponseHandler<UPostItunesPurchaseFailRequest*, UPaymentResultResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostItunesPurchaseFailRequest*,
                                                                                   TBeamFullResponseHandler<UPostItunesPurchaseFailRequest*, UPaymentResultResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPostTestPurchaseCancelRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPostTestPurchaseCancelRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPostTestPurchaseCancelRequest, UPaymentResultResponse>(
	const int64&, UPostTestPurchaseCancelRequest*, FOnPostTestPurchaseCancelSuccess, FOnPostTestPurchaseCancelError, FOnPostTestPurchaseCancelComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPostTestPurchaseCancelRequest, UPaymentResultResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostTestPurchaseCancelRequest*, FOnPostTestPurchaseCancelSuccess, FOnPostTestPurchaseCancelError, FOnPostTestPurchaseCancelComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPostTestPurchaseCancelRequest*, TBeamFullResponseHandler<UPostTestPurchaseCancelRequest*, UPaymentResultResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostTestPurchaseCancelRequest*,
                                                                                   TBeamFullResponseHandler<UPostTestPurchaseCancelRequest*, UPaymentResultResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPostTestPurchaseFailRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPostTestPurchaseFailRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPostTestPurchaseFailRequest, UPaymentResultResponse>(
	const int64&, UPostTestPurchaseFailRequest*, FOnPostTestPurchaseFailSuccess, FOnPostTestPurchaseFailError, FOnPostTestPurchaseFailComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPostTestPurchaseFailRequest, UPaymentResultResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostTestPurchaseFailRequest*, FOnPostTestPurchaseFailSuccess, FOnPostTestPurchaseFailError, FOnPostTestPurchaseFailComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPostTestPurchaseFailRequest*, TBeamFullResponseHandler<UPostTestPurchaseFailRequest*, UPaymentResultResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostTestPurchaseFailRequest*,
                                                                                   TBeamFullResponseHandler<UPostTestPurchaseFailRequest*, UPaymentResultResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPostCouponPurchaseCancelRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPostCouponPurchaseCancelRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPostCouponPurchaseCancelRequest, UPaymentResultResponse>(
	const int64&, UPostCouponPurchaseCancelRequest*, FOnPostCouponPurchaseCancelSuccess, FOnPostCouponPurchaseCancelError, FOnPostCouponPurchaseCancelComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPostCouponPurchaseCancelRequest, UPaymentResultResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostCouponPurchaseCancelRequest*, FOnPostCouponPurchaseCancelSuccess, FOnPostCouponPurchaseCancelError, FOnPostCouponPurchaseCancelComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPostCouponPurchaseCancelRequest*, TBeamFullResponseHandler<UPostCouponPurchaseCancelRequest*, UPaymentResultResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostCouponPurchaseCancelRequest*,
                                                                                   TBeamFullResponseHandler<UPostCouponPurchaseCancelRequest*, UPaymentResultResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPostCouponPurchaseBeginRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPostCouponPurchaseBeginRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPostCouponPurchaseBeginRequest, UBeginPurchaseResponse>(
	const int64&, UPostCouponPurchaseBeginRequest*, FOnPostCouponPurchaseBeginSuccess, FOnPostCouponPurchaseBeginError, FOnPostCouponPurchaseBeginComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPostCouponPurchaseBeginRequest, UBeginPurchaseResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostCouponPurchaseBeginRequest*, FOnPostCouponPurchaseBeginSuccess, FOnPostCouponPurchaseBeginError, FOnPostCouponPurchaseBeginComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPostCouponPurchaseBeginRequest*, TBeamFullResponseHandler<UPostCouponPurchaseBeginRequest*, UBeginPurchaseResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostCouponPurchaseBeginRequest*,
                                                                                   TBeamFullResponseHandler<UPostCouponPurchaseBeginRequest*, UBeginPurchaseResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPostFacebookPurchaseBeginRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPostFacebookPurchaseBeginRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPostFacebookPurchaseBeginRequest, UBeginPurchaseResponse>(
	const int64&, UPostFacebookPurchaseBeginRequest*, FOnPostFacebookPurchaseBeginSuccess, FOnPostFacebookPurchaseBeginError, FOnPostFacebookPurchaseBeginComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPostFacebookPurchaseBeginRequest, UBeginPurchaseResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostFacebookPurchaseBeginRequest*, FOnPostFacebookPurchaseBeginSuccess, FOnPostFacebookPurchaseBeginError, FOnPostFacebookPurchaseBeginComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPostFacebookPurchaseBeginRequest*, TBeamFullResponseHandler<UPostFacebookPurchaseBeginRequest*, UBeginPurchaseResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostFacebookPurchaseBeginRequest*,
                                                                                   TBeamFullResponseHandler<UPostFacebookPurchaseBeginRequest*, UBeginPurchaseResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UGetSteamOrderRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UGetSteamOrderRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UGetSteamOrderRequest, USteamOrderInfoResponse>(
	const int64&, UGetSteamOrderRequest*, FOnGetSteamOrderSuccess, FOnGetSteamOrderError, FOnGetSteamOrderComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UGetSteamOrderRequest, USteamOrderInfoResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetSteamOrderRequest*, FOnGetSteamOrderSuccess, FOnGetSteamOrderError, FOnGetSteamOrderComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UGetSteamOrderRequest*, TBeamFullResponseHandler<UGetSteamOrderRequest*, USteamOrderInfoResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetSteamOrderRequest*,
                                                                                   TBeamFullResponseHandler<UGetSteamOrderRequest*, USteamOrderInfoResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPostWindowsPurchaseBeginRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPostWindowsPurchaseBeginRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPostWindowsPurchaseBeginRequest, UBeginPurchaseResponse>(
	const int64&, UPostWindowsPurchaseBeginRequest*, FOnPostWindowsPurchaseBeginSuccess, FOnPostWindowsPurchaseBeginError, FOnPostWindowsPurchaseBeginComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPostWindowsPurchaseBeginRequest, UBeginPurchaseResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostWindowsPurchaseBeginRequest*, FOnPostWindowsPurchaseBeginSuccess, FOnPostWindowsPurchaseBeginError, FOnPostWindowsPurchaseBeginComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPostWindowsPurchaseBeginRequest*, TBeamFullResponseHandler<UPostWindowsPurchaseBeginRequest*, UBeginPurchaseResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostWindowsPurchaseBeginRequest*,
                                                                                   TBeamFullResponseHandler<UPostWindowsPurchaseBeginRequest*, UBeginPurchaseResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPostGoogleplayPurchaseFailRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPostGoogleplayPurchaseFailRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPostGoogleplayPurchaseFailRequest, UPaymentResultResponse>(
	const int64&, UPostGoogleplayPurchaseFailRequest*, FOnPostGoogleplayPurchaseFailSuccess, FOnPostGoogleplayPurchaseFailError, FOnPostGoogleplayPurchaseFailComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPostGoogleplayPurchaseFailRequest, UPaymentResultResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostGoogleplayPurchaseFailRequest*, FOnPostGoogleplayPurchaseFailSuccess, FOnPostGoogleplayPurchaseFailError, FOnPostGoogleplayPurchaseFailComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPostGoogleplayPurchaseFailRequest*, TBeamFullResponseHandler<UPostGoogleplayPurchaseFailRequest*, UPaymentResultResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostGoogleplayPurchaseFailRequest*,
                                                                                   TBeamFullResponseHandler<UPostGoogleplayPurchaseFailRequest*, UPaymentResultResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPostGoogleplayPurchaseCancelRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPostGoogleplayPurchaseCancelRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPostGoogleplayPurchaseCancelRequest, UPaymentResultResponse>(
	const int64&, UPostGoogleplayPurchaseCancelRequest*, FOnPostGoogleplayPurchaseCancelSuccess, FOnPostGoogleplayPurchaseCancelError, FOnPostGoogleplayPurchaseCancelComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPostGoogleplayPurchaseCancelRequest, UPaymentResultResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostGoogleplayPurchaseCancelRequest*, FOnPostGoogleplayPurchaseCancelSuccess, FOnPostGoogleplayPurchaseCancelError, FOnPostGoogleplayPurchaseCancelComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPostGoogleplayPurchaseCancelRequest*, TBeamFullResponseHandler<UPostGoogleplayPurchaseCancelRequest*, UPaymentResultResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostGoogleplayPurchaseCancelRequest*,
                                                                                   TBeamFullResponseHandler<UPostGoogleplayPurchaseCancelRequest*, UPaymentResultResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPostCouponPurchaseFailRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPostCouponPurchaseFailRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPostCouponPurchaseFailRequest, UPaymentResultResponse>(
	const int64&, UPostCouponPurchaseFailRequest*, FOnPostCouponPurchaseFailSuccess, FOnPostCouponPurchaseFailError, FOnPostCouponPurchaseFailComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPostCouponPurchaseFailRequest, UPaymentResultResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostCouponPurchaseFailRequest*, FOnPostCouponPurchaseFailSuccess, FOnPostCouponPurchaseFailError, FOnPostCouponPurchaseFailComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPostCouponPurchaseFailRequest*, TBeamFullResponseHandler<UPostCouponPurchaseFailRequest*, UPaymentResultResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostCouponPurchaseFailRequest*,
                                                                                   TBeamFullResponseHandler<UPostCouponPurchaseFailRequest*, UPaymentResultResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPostSteamPurchaseBeginRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPostSteamPurchaseBeginRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPostSteamPurchaseBeginRequest, UBeginPurchaseResponse>(
	const int64&, UPostSteamPurchaseBeginRequest*, FOnPostSteamPurchaseBeginSuccess, FOnPostSteamPurchaseBeginError, FOnPostSteamPurchaseBeginComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPostSteamPurchaseBeginRequest, UBeginPurchaseResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostSteamPurchaseBeginRequest*, FOnPostSteamPurchaseBeginSuccess, FOnPostSteamPurchaseBeginError, FOnPostSteamPurchaseBeginComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPostSteamPurchaseBeginRequest*, TBeamFullResponseHandler<UPostSteamPurchaseBeginRequest*, UBeginPurchaseResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostSteamPurchaseBeginRequest*,
                                                                                   TBeamFullResponseHandler<UPostSteamPurchaseBeginRequest*, UBeginPurchaseResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPostSteamPurchaseCancelRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPostSteamPurchaseCancelRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPostSteamPurchaseCancelRequest, UPaymentResultResponse>(
	const int64&, UPostSteamPurchaseCancelRequest*, FOnPostSteamPurchaseCancelSuccess, FOnPostSteamPurchaseCancelError, FOnPostSteamPurchaseCancelComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPostSteamPurchaseCancelRequest, UPaymentResultResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostSteamPurchaseCancelRequest*, FOnPostSteamPurchaseCancelSuccess, FOnPostSteamPurchaseCancelError, FOnPostSteamPurchaseCancelComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPostSteamPurchaseCancelRequest*, TBeamFullResponseHandler<UPostSteamPurchaseCancelRequest*, UPaymentResultResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostSteamPurchaseCancelRequest*,
                                                                                   TBeamFullResponseHandler<UPostSteamPurchaseCancelRequest*, UPaymentResultResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPostWindowsPurchaseCancelRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPostWindowsPurchaseCancelRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPostWindowsPurchaseCancelRequest, UPaymentResultResponse>(
	const int64&, UPostWindowsPurchaseCancelRequest*, FOnPostWindowsPurchaseCancelSuccess, FOnPostWindowsPurchaseCancelError, FOnPostWindowsPurchaseCancelComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPostWindowsPurchaseCancelRequest, UPaymentResultResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostWindowsPurchaseCancelRequest*, FOnPostWindowsPurchaseCancelSuccess, FOnPostWindowsPurchaseCancelError, FOnPostWindowsPurchaseCancelComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPostWindowsPurchaseCancelRequest*, TBeamFullResponseHandler<UPostWindowsPurchaseCancelRequest*, UPaymentResultResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostWindowsPurchaseCancelRequest*,
                                                                                   TBeamFullResponseHandler<UPostWindowsPurchaseCancelRequest*, UPaymentResultResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPostWindowsPurchaseFailRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPostWindowsPurchaseFailRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPostWindowsPurchaseFailRequest, UPaymentResultResponse>(
	const int64&, UPostWindowsPurchaseFailRequest*, FOnPostWindowsPurchaseFailSuccess, FOnPostWindowsPurchaseFailError, FOnPostWindowsPurchaseFailComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPostWindowsPurchaseFailRequest, UPaymentResultResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostWindowsPurchaseFailRequest*, FOnPostWindowsPurchaseFailSuccess, FOnPostWindowsPurchaseFailError, FOnPostWindowsPurchaseFailComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPostWindowsPurchaseFailRequest*, TBeamFullResponseHandler<UPostWindowsPurchaseFailRequest*, UPaymentResultResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostWindowsPurchaseFailRequest*,
                                                                                   TBeamFullResponseHandler<UPostWindowsPurchaseFailRequest*, UPaymentResultResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPostItunesPurchaseCancelRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPostItunesPurchaseCancelRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPostItunesPurchaseCancelRequest, UPaymentResultResponse>(
	const int64&, UPostItunesPurchaseCancelRequest*, FOnPostItunesPurchaseCancelSuccess, FOnPostItunesPurchaseCancelError, FOnPostItunesPurchaseCancelComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPostItunesPurchaseCancelRequest, UPaymentResultResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostItunesPurchaseCancelRequest*, FOnPostItunesPurchaseCancelSuccess, FOnPostItunesPurchaseCancelError, FOnPostItunesPurchaseCancelComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPostItunesPurchaseCancelRequest*, TBeamFullResponseHandler<UPostItunesPurchaseCancelRequest*, UPaymentResultResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostItunesPurchaseCancelRequest*,
                                                                                   TBeamFullResponseHandler<UPostItunesPurchaseCancelRequest*, UPaymentResultResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UBasicPushPostRegisterRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UBasicPushPostRegisterRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UBasicPushPostRegisterRequest, UEmptyRsp>(
	const int64&, UBasicPushPostRegisterRequest*, FOnBasicPushPostRegisterSuccess, FOnBasicPushPostRegisterError, FOnBasicPushPostRegisterComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UBasicPushPostRegisterRequest, UEmptyRsp>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UBasicPushPostRegisterRequest*, FOnBasicPushPostRegisterSuccess, FOnBasicPushPostRegisterError, FOnBasicPushPostRegisterComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UBasicPushPostRegisterRequest*, TBeamFullResponseHandler<UBasicPushPostRegisterRequest*, UEmptyRsp*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UBasicPushPostRegisterRequest*,
                                                                                   TBeamFullResponseHandler<UBasicPushPostRegisterRequest*, UEmptyRsp*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPostSendRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPostSendRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPostSendRequest, UEmptyRsp>(
	const int64&, UPostSendRequest*, FOnPostSendSuccess, FOnPostSendError, FOnPostSendComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPostSendRequest, UEmptyRsp>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostSendRequest*, FOnPostSendSuccess, FOnPostSendError, FOnPostSendComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPostSendRequest*, TBeamFullResponseHandler<UPostSendRequest*, UEmptyRsp*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostSendRequest*,
                                                                                   TBeamFullResponseHandler<UPostSendRequest*, UEmptyRsp*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPostPlayerRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPostPlayerRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPostPlayerRequest, UCommonResponse>(
	const int64&, UPostPlayerRequest*, FOnPostPlayerSuccess, FOnPostPlayerError, FOnPostPlayerComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPostPlayerRequest, UCommonResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostPlayerRequest*, FOnPostPlayerSuccess, FOnPostPlayerError, FOnPostPlayerComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPostPlayerRequest*, TBeamFullResponseHandler<UPostPlayerRequest*, UCommonResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostPlayerRequest*,
                                                                                   TBeamFullResponseHandler<UPostPlayerRequest*, UCommonResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPostCustomRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPostCustomRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPostCustomRequest, UCommonResponse>(
	const int64&, UPostCustomRequest*, FOnPostCustomSuccess, FOnPostCustomError, FOnPostCustomComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPostCustomRequest, UCommonResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostCustomRequest*, FOnPostCustomSuccess, FOnPostCustomError, FOnPostCustomComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPostCustomRequest*, TBeamFullResponseHandler<UPostCustomRequest*, UCommonResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostCustomRequest*,
                                                                                   TBeamFullResponseHandler<UPostCustomRequest*, UCommonResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPostServerRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPostServerRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPostServerRequest, UCommonResponse>(
	const int64&, UPostServerRequest*, FOnPostServerSuccess, FOnPostServerError, FOnPostServerComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPostServerRequest, UCommonResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostServerRequest*, FOnPostServerSuccess, FOnPostServerError, FOnPostServerComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPostServerRequest*, TBeamFullResponseHandler<UPostServerRequest*, UCommonResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostServerRequest*,
                                                                                   TBeamFullResponseHandler<UPostServerRequest*, UCommonResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPostGenericRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPostGenericRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPostGenericRequest, UCommonResponse>(
	const int64&, UPostGenericRequest*, FOnPostGenericSuccess, FOnPostGenericError, FOnPostGenericComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPostGenericRequest, UCommonResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostGenericRequest*, FOnPostGenericSuccess, FOnPostGenericError, FOnPostGenericComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPostGenericRequest*, TBeamFullResponseHandler<UPostGenericRequest*, UCommonResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostGenericRequest*,
                                                                                   TBeamFullResponseHandler<UPostGenericRequest*, UCommonResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UGetNotificationRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UGetNotificationRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UGetNotificationRequest, USubscriberDetailsResponse>(
	const int64&, UGetNotificationRequest*, FOnGetNotificationSuccess, FOnGetNotificationError, FOnGetNotificationComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UGetNotificationRequest, USubscriberDetailsResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetNotificationRequest*, FOnGetNotificationSuccess, FOnGetNotificationError, FOnGetNotificationComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UGetNotificationRequest*, TBeamFullResponseHandler<UGetNotificationRequest*, USubscriberDetailsResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetNotificationRequest*,
                                                                                   TBeamFullResponseHandler<UGetNotificationRequest*, USubscriberDetailsResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UBasicNotificationPostGameRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UBasicNotificationPostGameRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UBasicNotificationPostGameRequest, UCommonResponse>(
	const int64&, UBasicNotificationPostGameRequest*, FOnBasicNotificationPostGameSuccess, FOnBasicNotificationPostGameError, FOnBasicNotificationPostGameComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UBasicNotificationPostGameRequest, UCommonResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UBasicNotificationPostGameRequest*, FOnBasicNotificationPostGameSuccess, FOnBasicNotificationPostGameError, FOnBasicNotificationPostGameComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UBasicNotificationPostGameRequest*, TBeamFullResponseHandler<UBasicNotificationPostGameRequest*, UCommonResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UBasicNotificationPostGameRequest*,
                                                                                   TBeamFullResponseHandler<UBasicNotificationPostGameRequest*, UCommonResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UGetCustomerAliasAvailableRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UGetCustomerAliasAvailableRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UGetCustomerAliasAvailableRequest, UAliasAvailableResponse>(
	const int64&, UGetCustomerAliasAvailableRequest*, FOnGetCustomerAliasAvailableSuccess, FOnGetCustomerAliasAvailableError, FOnGetCustomerAliasAvailableComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UGetCustomerAliasAvailableRequest, UAliasAvailableResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetCustomerAliasAvailableRequest*, FOnGetCustomerAliasAvailableSuccess, FOnGetCustomerAliasAvailableError, FOnGetCustomerAliasAvailableComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UGetCustomerAliasAvailableRequest*, TBeamFullResponseHandler<UGetCustomerAliasAvailableRequest*, UAliasAvailableResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetCustomerAliasAvailableRequest*,
                                                                                   TBeamFullResponseHandler<UGetCustomerAliasAvailableRequest*, UAliasAvailableResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UGetProjectRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UGetProjectRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UGetProjectRequest, UProjectView>(
	const int64&, UGetProjectRequest*, FOnGetProjectSuccess, FOnGetProjectError, FOnGetProjectComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UGetProjectRequest, UProjectView>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetProjectRequest*, FOnGetProjectSuccess, FOnGetProjectError, FOnGetProjectComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UGetProjectRequest*, TBeamFullResponseHandler<UGetProjectRequest*, UProjectView*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetProjectRequest*,
                                                                                   TBeamFullResponseHandler<UGetProjectRequest*, UProjectView*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPostCustomerRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPostCustomerRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPostCustomerRequest, UNewCustomerResponse>(
	const int64&, UPostCustomerRequest*, FOnPostCustomerSuccess, FOnPostCustomerError, FOnPostCustomerComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPostCustomerRequest, UNewCustomerResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostCustomerRequest*, FOnPostCustomerSuccess, FOnPostCustomerError, FOnPostCustomerComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPostCustomerRequest*, TBeamFullResponseHandler<UPostCustomerRequest*, UNewCustomerResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostCustomerRequest*,
                                                                                   TBeamFullResponseHandler<UPostCustomerRequest*, UNewCustomerResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UGetIsCustomerRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UGetIsCustomerRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UGetIsCustomerRequest, UEmptyResponse>(
	const int64&, UGetIsCustomerRequest*, FOnGetIsCustomerSuccess, FOnGetIsCustomerError, FOnGetIsCustomerComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UGetIsCustomerRequest, UEmptyResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetIsCustomerRequest*, FOnGetIsCustomerSuccess, FOnGetIsCustomerError, FOnGetIsCustomerComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UGetIsCustomerRequest*, TBeamFullResponseHandler<UGetIsCustomerRequest*, UEmptyResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetIsCustomerRequest*,
                                                                                   TBeamFullResponseHandler<UGetIsCustomerRequest*, UEmptyResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UGetCustomersRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UGetCustomersRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UGetCustomersRequest, UCustomersResponse>(
	const int64&, UGetCustomersRequest*, FOnGetCustomersSuccess, FOnGetCustomersError, FOnGetCustomersComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UGetCustomersRequest, UCustomersResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetCustomersRequest*, FOnGetCustomersSuccess, FOnGetCustomersError, FOnGetCustomersComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UGetCustomersRequest*, TBeamFullResponseHandler<UGetCustomersRequest*, UCustomersResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetCustomersRequest*,
                                                                                   TBeamFullResponseHandler<UGetCustomersRequest*, UCustomersResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPostProjectBeamableRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPostProjectBeamableRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPostProjectBeamableRequest, UCommonResponse>(
	const int64&, UPostProjectBeamableRequest*, FOnPostProjectBeamableSuccess, FOnPostProjectBeamableError, FOnPostProjectBeamableComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPostProjectBeamableRequest, UCommonResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostProjectBeamableRequest*, FOnPostProjectBeamableSuccess, FOnPostProjectBeamableError, FOnPostProjectBeamableComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPostProjectBeamableRequest*, TBeamFullResponseHandler<UPostProjectBeamableRequest*, UCommonResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostProjectBeamableRequest*,
                                                                                   TBeamFullResponseHandler<UPostProjectBeamableRequest*, UCommonResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPostProjectRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPostProjectRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPostProjectRequest, UCommonResponse>(
	const int64&, UPostProjectRequest*, FOnPostProjectSuccess, FOnPostProjectError, FOnPostProjectComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPostProjectRequest, UCommonResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostProjectRequest*, FOnPostProjectSuccess, FOnPostProjectError, FOnPostProjectComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPostProjectRequest*, TBeamFullResponseHandler<UPostProjectRequest*, UCommonResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostProjectRequest*,
                                                                                   TBeamFullResponseHandler<UPostProjectRequest*, UCommonResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPutProjectRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPutProjectRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPutProjectRequest, UCommonResponse>(
	const int64&, UPutProjectRequest*, FOnPutProjectSuccess, FOnPutProjectError, FOnPutProjectComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPutProjectRequest, UCommonResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPutProjectRequest*, FOnPutProjectSuccess, FOnPutProjectError, FOnPutProjectComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPutProjectRequest*, TBeamFullResponseHandler<UPutProjectRequest*, UCommonResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPutProjectRequest*,
                                                                                   TBeamFullResponseHandler<UPutProjectRequest*, UCommonResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UDeleteProjectRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UDeleteProjectRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UDeleteProjectRequest, UCommonResponse>(
	const int64&, UDeleteProjectRequest*, FOnDeleteProjectSuccess, FOnDeleteProjectError, FOnDeleteProjectComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UDeleteProjectRequest, UCommonResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UDeleteProjectRequest*, FOnDeleteProjectSuccess, FOnDeleteProjectError, FOnDeleteProjectComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UDeleteProjectRequest*, TBeamFullResponseHandler<UDeleteProjectRequest*, UCommonResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UDeleteProjectRequest*,
                                                                                   TBeamFullResponseHandler<UDeleteProjectRequest*, UCommonResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UGetGamesRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UGetGamesRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UGetGamesRequest, UGetGameResponse>(
	const int64&, UGetGamesRequest*, FOnGetGamesSuccess, FOnGetGamesError, FOnGetGamesComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UGetGamesRequest, UGetGameResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetGamesRequest*, FOnGetGamesSuccess, FOnGetGamesError, FOnGetGamesComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UGetGamesRequest*, TBeamFullResponseHandler<UGetGamesRequest*, UGetGameResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetGamesRequest*,
                                                                                   TBeamFullResponseHandler<UGetGamesRequest*, UGetGameResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UGetConfigRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UGetConfigRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UGetConfigRequest, URealmConfigResponse>(
	const int64&, UGetConfigRequest*, FOnGetConfigSuccess, FOnGetConfigError, FOnGetConfigComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UGetConfigRequest, URealmConfigResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetConfigRequest*, FOnGetConfigSuccess, FOnGetConfigError, FOnGetConfigComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UGetConfigRequest*, TBeamFullResponseHandler<UGetConfigRequest*, URealmConfigResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetConfigRequest*,
                                                                                   TBeamFullResponseHandler<UGetConfigRequest*, URealmConfigResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPutConfigRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPutConfigRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPutConfigRequest, UCommonResponse>(
	const int64&, UPutConfigRequest*, FOnPutConfigSuccess, FOnPutConfigError, FOnPutConfigComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPutConfigRequest, UCommonResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPutConfigRequest*, FOnPutConfigSuccess, FOnPutConfigError, FOnPutConfigComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPutConfigRequest*, TBeamFullResponseHandler<UPutConfigRequest*, UCommonResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPutConfigRequest*,
                                                                                   TBeamFullResponseHandler<UPutConfigRequest*, UCommonResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPutProjectRenameRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPutProjectRenameRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPutProjectRenameRequest, UCommonResponse>(
	const int64&, UPutProjectRenameRequest*, FOnPutProjectRenameSuccess, FOnPutProjectRenameError, FOnPutProjectRenameComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPutProjectRenameRequest, UCommonResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPutProjectRenameRequest*, FOnPutProjectRenameSuccess, FOnPutProjectRenameError, FOnPutProjectRenameComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPutProjectRenameRequest*, TBeamFullResponseHandler<UPutProjectRenameRequest*, UCommonResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPutProjectRenameRequest*,
                                                                                   TBeamFullResponseHandler<UPutProjectRenameRequest*, UCommonResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UGetPlansRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UGetPlansRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UGetPlansRequest, UServicePlansResponse>(
	const int64&, UGetPlansRequest*, FOnGetPlansSuccess, FOnGetPlansError, FOnGetPlansComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UGetPlansRequest, UServicePlansResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetPlansRequest*, FOnGetPlansSuccess, FOnGetPlansError, FOnGetPlansComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UGetPlansRequest*, TBeamFullResponseHandler<UGetPlansRequest*, UServicePlansResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetPlansRequest*,
                                                                                   TBeamFullResponseHandler<UGetPlansRequest*, UServicePlansResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPostPlansRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPostPlansRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPostPlansRequest, UCommonResponse>(
	const int64&, UPostPlansRequest*, FOnPostPlansSuccess, FOnPostPlansError, FOnPostPlansComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPostPlansRequest, UCommonResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostPlansRequest*, FOnPostPlansSuccess, FOnPostPlansError, FOnPostPlansComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPostPlansRequest*, TBeamFullResponseHandler<UPostPlansRequest*, UCommonResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostPlansRequest*,
                                                                                   TBeamFullResponseHandler<UPostPlansRequest*, UCommonResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UGetCustomerRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UGetCustomerRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UGetCustomerRequest, UCustomerViewResponse>(
	const int64&, UGetCustomerRequest*, FOnGetCustomerSuccess, FOnGetCustomerError, FOnGetCustomerComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UGetCustomerRequest, UCustomerViewResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetCustomerRequest*, FOnGetCustomerSuccess, FOnGetCustomerError, FOnGetCustomerComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UGetCustomerRequest*, TBeamFullResponseHandler<UGetCustomerRequest*, UCustomerViewResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetCustomerRequest*,
                                                                                   TBeamFullResponseHandler<UGetCustomerRequest*, UCustomerViewResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UGetLaunchMessageRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UGetLaunchMessageRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UGetLaunchMessageRequest, ULaunchMessageListResponse>(
	const int64&, UGetLaunchMessageRequest*, FOnGetLaunchMessageSuccess, FOnGetLaunchMessageError, FOnGetLaunchMessageComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UGetLaunchMessageRequest, ULaunchMessageListResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetLaunchMessageRequest*, FOnGetLaunchMessageSuccess, FOnGetLaunchMessageError, FOnGetLaunchMessageComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UGetLaunchMessageRequest*, TBeamFullResponseHandler<UGetLaunchMessageRequest*, ULaunchMessageListResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetLaunchMessageRequest*,
                                                                                   TBeamFullResponseHandler<UGetLaunchMessageRequest*, ULaunchMessageListResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPostLaunchMessageRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPostLaunchMessageRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPostLaunchMessageRequest, UCommonResponse>(
	const int64&, UPostLaunchMessageRequest*, FOnPostLaunchMessageSuccess, FOnPostLaunchMessageError, FOnPostLaunchMessageComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPostLaunchMessageRequest, UCommonResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostLaunchMessageRequest*, FOnPostLaunchMessageSuccess, FOnPostLaunchMessageError, FOnPostLaunchMessageComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPostLaunchMessageRequest*, TBeamFullResponseHandler<UPostLaunchMessageRequest*, UCommonResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostLaunchMessageRequest*,
                                                                                   TBeamFullResponseHandler<UPostLaunchMessageRequest*, UCommonResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UDeleteLaunchMessageRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UDeleteLaunchMessageRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UDeleteLaunchMessageRequest, UCommonResponse>(
	const int64&, UDeleteLaunchMessageRequest*, FOnDeleteLaunchMessageSuccess, FOnDeleteLaunchMessageError, FOnDeleteLaunchMessageComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UDeleteLaunchMessageRequest, UCommonResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UDeleteLaunchMessageRequest*, FOnDeleteLaunchMessageSuccess, FOnDeleteLaunchMessageError, FOnDeleteLaunchMessageComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UDeleteLaunchMessageRequest*, TBeamFullResponseHandler<UDeleteLaunchMessageRequest*, UCommonResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UDeleteLaunchMessageRequest*,
                                                                                   TBeamFullResponseHandler<UDeleteLaunchMessageRequest*, UCommonResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UGetAdminCustomerRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UGetAdminCustomerRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UGetAdminCustomerRequest, UCustomerResponse>(
	const int64&, UGetAdminCustomerRequest*, FOnGetAdminCustomerSuccess, FOnGetAdminCustomerError, FOnGetAdminCustomerComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UGetAdminCustomerRequest, UCustomerResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetAdminCustomerRequest*, FOnGetAdminCustomerSuccess, FOnGetAdminCustomerError, FOnGetAdminCustomerComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UGetAdminCustomerRequest*, TBeamFullResponseHandler<UGetAdminCustomerRequest*, UCustomerResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetAdminCustomerRequest*,
                                                                                   TBeamFullResponseHandler<UGetAdminCustomerRequest*, UCustomerResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UGetGameRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UGetGameRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UGetGameRequest, UGetGameResponse>(
	const int64&, UGetGameRequest*, FOnGetGameSuccess, FOnGetGameError, FOnGetGameComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UGetGameRequest, UGetGameResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetGameRequest*, FOnGetGameSuccess, FOnGetGameError, FOnGetGameComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UGetGameRequest*, TBeamFullResponseHandler<UGetGameRequest*, UGetGameResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetGameRequest*,
                                                                                   TBeamFullResponseHandler<UGetGameRequest*, UGetGameResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UBasicRealmsPostGameRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UBasicRealmsPostGameRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UBasicRealmsPostGameRequest, UCommonResponse>(
	const int64&, UBasicRealmsPostGameRequest*, FOnBasicRealmsPostGameSuccess, FOnBasicRealmsPostGameError, FOnBasicRealmsPostGameComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UBasicRealmsPostGameRequest, UCommonResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UBasicRealmsPostGameRequest*, FOnBasicRealmsPostGameSuccess, FOnBasicRealmsPostGameError, FOnBasicRealmsPostGameComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UBasicRealmsPostGameRequest*, TBeamFullResponseHandler<UBasicRealmsPostGameRequest*, UCommonResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UBasicRealmsPostGameRequest*,
                                                                                   TBeamFullResponseHandler<UBasicRealmsPostGameRequest*, UCommonResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPutGameRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPutGameRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPutGameRequest, UCommonResponse>(
	const int64&, UPutGameRequest*, FOnPutGameSuccess, FOnPutGameError, FOnPutGameComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPutGameRequest, UCommonResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPutGameRequest*, FOnPutGameSuccess, FOnPutGameError, FOnPutGameComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPutGameRequest*, TBeamFullResponseHandler<UPutGameRequest*, UCommonResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPutGameRequest*,
                                                                                   TBeamFullResponseHandler<UPutGameRequest*, UCommonResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UGetProjectPromoteRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UGetProjectPromoteRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UGetProjectPromoteRequest, UPromoteRealmResponseOld>(
	const int64&, UGetProjectPromoteRequest*, FOnGetProjectPromoteSuccess, FOnGetProjectPromoteError, FOnGetProjectPromoteComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UGetProjectPromoteRequest, UPromoteRealmResponseOld>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetProjectPromoteRequest*, FOnGetProjectPromoteSuccess, FOnGetProjectPromoteError, FOnGetProjectPromoteComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UGetProjectPromoteRequest*, TBeamFullResponseHandler<UGetProjectPromoteRequest*, UPromoteRealmResponseOld*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetProjectPromoteRequest*,
                                                                                   TBeamFullResponseHandler<UGetProjectPromoteRequest*, UPromoteRealmResponseOld*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPostProjectPromoteRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPostProjectPromoteRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPostProjectPromoteRequest, UPromoteRealmResponseOld>(
	const int64&, UPostProjectPromoteRequest*, FOnPostProjectPromoteSuccess, FOnPostProjectPromoteError, FOnPostProjectPromoteComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPostProjectPromoteRequest, UPromoteRealmResponseOld>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostProjectPromoteRequest*, FOnPostProjectPromoteSuccess, FOnPostProjectPromoteError, FOnPostProjectPromoteComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPostProjectPromoteRequest*, TBeamFullResponseHandler<UPostProjectPromoteRequest*, UPromoteRealmResponseOld*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostProjectPromoteRequest*,
                                                                                   TBeamFullResponseHandler<UPostProjectPromoteRequest*, UPromoteRealmResponseOld*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UGetPromotionRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UGetPromotionRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UGetPromotionRequest, UPromoteRealmResponse>(
	const int64&, UGetPromotionRequest*, FOnGetPromotionSuccess, FOnGetPromotionError, FOnGetPromotionComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UGetPromotionRequest, UPromoteRealmResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetPromotionRequest*, FOnGetPromotionSuccess, FOnGetPromotionError, FOnGetPromotionComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UGetPromotionRequest*, TBeamFullResponseHandler<UGetPromotionRequest*, UPromoteRealmResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetPromotionRequest*,
                                                                                   TBeamFullResponseHandler<UGetPromotionRequest*, UPromoteRealmResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPostPromotionRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPostPromotionRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPostPromotionRequest, UPromoteRealmResponse>(
	const int64&, UPostPromotionRequest*, FOnPostPromotionSuccess, FOnPostPromotionError, FOnPostPromotionComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPostPromotionRequest, UPromoteRealmResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostPromotionRequest*, FOnPostPromotionSuccess, FOnPostPromotionError, FOnPostPromotionComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPostPromotionRequest*, TBeamFullResponseHandler<UPostPromotionRequest*, UPromoteRealmResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostPromotionRequest*,
                                                                                   TBeamFullResponseHandler<UPostPromotionRequest*, UPromoteRealmResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UGetMyRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UGetMyRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UGetMyRequest, USocial>(
	const int64&, UGetMyRequest*, FOnGetMySuccess, FOnGetMyError, FOnGetMyComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UGetMyRequest, USocial>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetMyRequest*, FOnGetMySuccess, FOnGetMyError, FOnGetMyComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UGetMyRequest*, TBeamFullResponseHandler<UGetMyRequest*, USocial*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetMyRequest*,
                                                                                   TBeamFullResponseHandler<UGetMyRequest*, USocial*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPostFriendsInviteRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPostFriendsInviteRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPostFriendsInviteRequest, UEmptyResponse>(
	const int64&, UPostFriendsInviteRequest*, FOnPostFriendsInviteSuccess, FOnPostFriendsInviteError, FOnPostFriendsInviteComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPostFriendsInviteRequest, UEmptyResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostFriendsInviteRequest*, FOnPostFriendsInviteSuccess, FOnPostFriendsInviteError, FOnPostFriendsInviteComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPostFriendsInviteRequest*, TBeamFullResponseHandler<UPostFriendsInviteRequest*, UEmptyResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostFriendsInviteRequest*,
                                                                                   TBeamFullResponseHandler<UPostFriendsInviteRequest*, UEmptyResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UDeleteFriendsInviteRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UDeleteFriendsInviteRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UDeleteFriendsInviteRequest, UEmptyResponse>(
	const int64&, UDeleteFriendsInviteRequest*, FOnDeleteFriendsInviteSuccess, FOnDeleteFriendsInviteError, FOnDeleteFriendsInviteComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UDeleteFriendsInviteRequest, UEmptyResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UDeleteFriendsInviteRequest*, FOnDeleteFriendsInviteSuccess, FOnDeleteFriendsInviteError, FOnDeleteFriendsInviteComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UDeleteFriendsInviteRequest*, TBeamFullResponseHandler<UDeleteFriendsInviteRequest*, UEmptyResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UDeleteFriendsInviteRequest*,
                                                                                   TBeamFullResponseHandler<UDeleteFriendsInviteRequest*, UEmptyResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UDeleteFriendsRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UDeleteFriendsRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UDeleteFriendsRequest, UEmptyResponse>(
	const int64&, UDeleteFriendsRequest*, FOnDeleteFriendsSuccess, FOnDeleteFriendsError, FOnDeleteFriendsComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UDeleteFriendsRequest, UEmptyResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UDeleteFriendsRequest*, FOnDeleteFriendsSuccess, FOnDeleteFriendsError, FOnDeleteFriendsComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UDeleteFriendsRequest*, TBeamFullResponseHandler<UDeleteFriendsRequest*, UEmptyResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UDeleteFriendsRequest*,
                                                                                   TBeamFullResponseHandler<UDeleteFriendsRequest*, UEmptyResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPostFriendsImportRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPostFriendsImportRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPostFriendsImportRequest, UEmptyResponse>(
	const int64&, UPostFriendsImportRequest*, FOnPostFriendsImportSuccess, FOnPostFriendsImportError, FOnPostFriendsImportComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPostFriendsImportRequest, UEmptyResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostFriendsImportRequest*, FOnPostFriendsImportSuccess, FOnPostFriendsImportError, FOnPostFriendsImportComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPostFriendsImportRequest*, TBeamFullResponseHandler<UPostFriendsImportRequest*, UEmptyResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostFriendsImportRequest*,
                                                                                   TBeamFullResponseHandler<UPostFriendsImportRequest*, UEmptyResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPostFriendsMakeRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPostFriendsMakeRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPostFriendsMakeRequest, UCommonResponse>(
	const int64&, UPostFriendsMakeRequest*, FOnPostFriendsMakeSuccess, FOnPostFriendsMakeError, FOnPostFriendsMakeComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPostFriendsMakeRequest, UCommonResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostFriendsMakeRequest*, FOnPostFriendsMakeSuccess, FOnPostFriendsMakeError, FOnPostFriendsMakeComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPostFriendsMakeRequest*, TBeamFullResponseHandler<UPostFriendsMakeRequest*, UCommonResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostFriendsMakeRequest*,
                                                                                   TBeamFullResponseHandler<UPostFriendsMakeRequest*, UCommonResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UGetSocialRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UGetSocialRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UGetSocialRequest, UGetSocialStatusesResponse>(
	const int64&, UGetSocialRequest*, FOnGetSocialSuccess, FOnGetSocialError, FOnGetSocialComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UGetSocialRequest, UGetSocialStatusesResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetSocialRequest*, FOnGetSocialSuccess, FOnGetSocialError, FOnGetSocialComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UGetSocialRequest*, TBeamFullResponseHandler<UGetSocialRequest*, UGetSocialStatusesResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetSocialRequest*,
                                                                                   TBeamFullResponseHandler<UGetSocialRequest*, UGetSocialStatusesResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPostBlockedRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPostBlockedRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPostBlockedRequest, UFriendshipStatus>(
	const int64&, UPostBlockedRequest*, FOnPostBlockedSuccess, FOnPostBlockedError, FOnPostBlockedComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPostBlockedRequest, UFriendshipStatus>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostBlockedRequest*, FOnPostBlockedSuccess, FOnPostBlockedError, FOnPostBlockedComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPostBlockedRequest*, TBeamFullResponseHandler<UPostBlockedRequest*, UFriendshipStatus*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostBlockedRequest*,
                                                                                   TBeamFullResponseHandler<UPostBlockedRequest*, UFriendshipStatus*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UDeleteBlockedRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UDeleteBlockedRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UDeleteBlockedRequest, UFriendshipStatus>(
	const int64&, UDeleteBlockedRequest*, FOnDeleteBlockedSuccess, FOnDeleteBlockedError, FOnDeleteBlockedComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UDeleteBlockedRequest, UFriendshipStatus>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UDeleteBlockedRequest*, FOnDeleteBlockedSuccess, FOnDeleteBlockedError, FOnDeleteBlockedComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UDeleteBlockedRequest*, TBeamFullResponseHandler<UDeleteBlockedRequest*, UFriendshipStatus*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UDeleteBlockedRequest*,
                                                                                   TBeamFullResponseHandler<UDeleteBlockedRequest*, UFriendshipStatus*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UGetRoomsRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UGetRoomsRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UGetRoomsRequest, UGetRoomsResponse>(
	const int64&, UGetRoomsRequest*, FOnGetRoomsSuccess, FOnGetRoomsError, FOnGetRoomsComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UGetRoomsRequest, UGetRoomsResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetRoomsRequest*, FOnGetRoomsSuccess, FOnGetRoomsError, FOnGetRoomsComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UGetRoomsRequest*, TBeamFullResponseHandler<UGetRoomsRequest*, UGetRoomsResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetRoomsRequest*,
                                                                                   TBeamFullResponseHandler<UGetRoomsRequest*, UGetRoomsResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPostRoomsRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPostRoomsRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPostRoomsRequest, UCreateRoomResponse>(
	const int64&, UPostRoomsRequest*, FOnPostRoomsSuccess, FOnPostRoomsError, FOnPostRoomsComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPostRoomsRequest, UCreateRoomResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostRoomsRequest*, FOnPostRoomsSuccess, FOnPostRoomsError, FOnPostRoomsComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPostRoomsRequest*, TBeamFullResponseHandler<UPostRoomsRequest*, UCreateRoomResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostRoomsRequest*,
                                                                                   TBeamFullResponseHandler<UPostRoomsRequest*, UCreateRoomResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UDeleteRoomsRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UDeleteRoomsRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UDeleteRoomsRequest, ULeaveRoomResponse>(
	const int64&, UDeleteRoomsRequest*, FOnDeleteRoomsSuccess, FOnDeleteRoomsError, FOnDeleteRoomsComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UDeleteRoomsRequest, ULeaveRoomResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UDeleteRoomsRequest*, FOnDeleteRoomsSuccess, FOnDeleteRoomsError, FOnDeleteRoomsComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UDeleteRoomsRequest*, TBeamFullResponseHandler<UDeleteRoomsRequest*, ULeaveRoomResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UDeleteRoomsRequest*,
                                                                                   TBeamFullResponseHandler<UDeleteRoomsRequest*, ULeaveRoomResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UGetChatV2Request*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UGetChatV2Request*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UGetChatV2Request, UGetRoomsResponse>(
	const int64&, UGetChatV2Request*, FOnGetChatV2Success, FOnGetChatV2Error, FOnGetChatV2Complete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UGetChatV2Request, UGetRoomsResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetChatV2Request*, FOnGetChatV2Success, FOnGetChatV2Error, FOnGetChatV2Complete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UGetChatV2Request*, TBeamFullResponseHandler<UGetChatV2Request*, UGetRoomsResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetChatV2Request*,
                                                                                   TBeamFullResponseHandler<UGetChatV2Request*, UGetRoomsResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPostMessagesRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPostMessagesRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPostMessagesRequest, USendMessageResponse>(
	const int64&, UPostMessagesRequest*, FOnPostMessagesSuccess, FOnPostMessagesError, FOnPostMessagesComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPostMessagesRequest, USendMessageResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostMessagesRequest*, FOnPostMessagesSuccess, FOnPostMessagesError, FOnPostMessagesComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPostMessagesRequest*, TBeamFullResponseHandler<UPostMessagesRequest*, USendMessageResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostMessagesRequest*,
                                                                                   TBeamFullResponseHandler<UPostMessagesRequest*, USendMessageResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPutTickRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPutTickRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPutTickRequest, UEmptyResponse>(
	const int64&, UPutTickRequest*, FOnPutTickSuccess, FOnPutTickError, FOnPutTickComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPutTickRequest, UEmptyResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPutTickRequest*, FOnPutTickSuccess, FOnPutTickError, FOnPutTickComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPutTickRequest*, TBeamFullResponseHandler<UPutTickRequest*, UEmptyResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPutTickRequest*,
                                                                                   TBeamFullResponseHandler<UPutTickRequest*, UEmptyResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UGetMatchRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UGetMatchRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UGetMatchRequest, UMatchUpdate>(
	const int64&, UGetMatchRequest*, FOnGetMatchSuccess, FOnGetMatchError, FOnGetMatchComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UGetMatchRequest, UMatchUpdate>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetMatchRequest*, FOnGetMatchSuccess, FOnGetMatchError, FOnGetMatchComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UGetMatchRequest*, TBeamFullResponseHandler<UGetMatchRequest*, UMatchUpdate*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetMatchRequest*,
                                                                                   TBeamFullResponseHandler<UGetMatchRequest*, UMatchUpdate*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPostMatchRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPostMatchRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPostMatchRequest, UMatchUpdate>(
	const int64&, UPostMatchRequest*, FOnPostMatchSuccess, FOnPostMatchError, FOnPostMatchComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPostMatchRequest, UMatchUpdate>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostMatchRequest*, FOnPostMatchSuccess, FOnPostMatchError, FOnPostMatchComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPostMatchRequest*, TBeamFullResponseHandler<UPostMatchRequest*, UMatchUpdate*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostMatchRequest*,
                                                                                   TBeamFullResponseHandler<UPostMatchRequest*, UMatchUpdate*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UDeleteMatchRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UDeleteMatchRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UDeleteMatchRequest, UEmptyResponse>(
	const int64&, UDeleteMatchRequest*, FOnDeleteMatchSuccess, FOnDeleteMatchError, FOnDeleteMatchComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UDeleteMatchRequest, UEmptyResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UDeleteMatchRequest*, FOnDeleteMatchSuccess, FOnDeleteMatchError, FOnDeleteMatchComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UDeleteMatchRequest*, TBeamFullResponseHandler<UDeleteMatchRequest*, UEmptyResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UDeleteMatchRequest*,
                                                                                   TBeamFullResponseHandler<UDeleteMatchRequest*, UEmptyResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UGetSkusRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UGetSkusRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UGetSkusRequest, UGetSKUsResponse>(
	const int64&, UGetSkusRequest*, FOnGetSkusSuccess, FOnGetSkusError, FOnGetSkusComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UGetSkusRequest, UGetSKUsResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetSkusRequest*, FOnGetSkusSuccess, FOnGetSkusError, FOnGetSkusComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UGetSkusRequest*, TBeamFullResponseHandler<UGetSkusRequest*, UGetSKUsResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetSkusRequest*,
                                                                                   TBeamFullResponseHandler<UGetSkusRequest*, UGetSKUsResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UGetCouponsCountRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UGetCouponsCountRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UGetCouponsCountRequest, UGetTotalCouponResponse>(
	const int64&, UGetCouponsCountRequest*, FOnGetCouponsCountSuccess, FOnGetCouponsCountError, FOnGetCouponsCountComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UGetCouponsCountRequest, UGetTotalCouponResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetCouponsCountRequest*, FOnGetCouponsCountSuccess, FOnGetCouponsCountError, FOnGetCouponsCountComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UGetCouponsCountRequest*, TBeamFullResponseHandler<UGetCouponsCountRequest*, UGetTotalCouponResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetCouponsCountRequest*,
                                                                                   TBeamFullResponseHandler<UGetCouponsCountRequest*, UGetTotalCouponResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPostCatalogLegacyRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPostCatalogLegacyRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPostCatalogLegacyRequest, UResultResponse>(
	const int64&, UPostCatalogLegacyRequest*, FOnPostCatalogLegacySuccess, FOnPostCatalogLegacyError, FOnPostCatalogLegacyComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPostCatalogLegacyRequest, UResultResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostCatalogLegacyRequest*, FOnPostCatalogLegacySuccess, FOnPostCatalogLegacyError, FOnPostCatalogLegacyComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPostCatalogLegacyRequest*, TBeamFullResponseHandler<UPostCatalogLegacyRequest*, UResultResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostCatalogLegacyRequest*,
                                                                                   TBeamFullResponseHandler<UPostCatalogLegacyRequest*, UResultResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UGetCatalogRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UGetCatalogRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UGetCatalogRequest, UGetCatalogResponse>(
	const int64&, UGetCatalogRequest*, FOnGetCatalogSuccess, FOnGetCatalogError, FOnGetCatalogComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UGetCatalogRequest, UGetCatalogResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetCatalogRequest*, FOnGetCatalogSuccess, FOnGetCatalogError, FOnGetCatalogComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UGetCatalogRequest*, TBeamFullResponseHandler<UGetCatalogRequest*, UGetCatalogResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetCatalogRequest*,
                                                                                   TBeamFullResponseHandler<UGetCatalogRequest*, UGetCatalogResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPostSkusRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPostSkusRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPostSkusRequest, UResultResponse>(
	const int64&, UPostSkusRequest*, FOnPostSkusSuccess, FOnPostSkusError, FOnPostSkusComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPostSkusRequest, UResultResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostSkusRequest*, FOnPostSkusSuccess, FOnPostSkusError, FOnPostSkusComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPostSkusRequest*, TBeamFullResponseHandler<UPostSkusRequest*, UResultResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostSkusRequest*,
                                                                                   TBeamFullResponseHandler<UPostSkusRequest*, UResultResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UGetCommerceRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UGetCommerceRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UGetCommerceRequest, UGetActiveOffersResponse>(
	const int64&, UGetCommerceRequest*, FOnGetCommerceSuccess, FOnGetCommerceError, FOnGetCommerceComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UGetCommerceRequest, UGetActiveOffersResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetCommerceRequest*, FOnGetCommerceSuccess, FOnGetCommerceError, FOnGetCommerceComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UGetCommerceRequest*, TBeamFullResponseHandler<UGetCommerceRequest*, UGetActiveOffersResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetCommerceRequest*,
                                                                                   TBeamFullResponseHandler<UGetCommerceRequest*, UGetActiveOffersResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPutListingsCooldownRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPutListingsCooldownRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPutListingsCooldownRequest, UCommonResponse>(
	const int64&, UPutListingsCooldownRequest*, FOnPutListingsCooldownSuccess, FOnPutListingsCooldownError, FOnPutListingsCooldownComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPutListingsCooldownRequest, UCommonResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPutListingsCooldownRequest*, FOnPutListingsCooldownSuccess, FOnPutListingsCooldownError, FOnPutListingsCooldownComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPutListingsCooldownRequest*, TBeamFullResponseHandler<UPutListingsCooldownRequest*, UCommonResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPutListingsCooldownRequest*,
                                                                                   TBeamFullResponseHandler<UPutListingsCooldownRequest*, UCommonResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UGetOffersAdminRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UGetOffersAdminRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UGetOffersAdminRequest, UGetActiveOffersResponse>(
	const int64&, UGetOffersAdminRequest*, FOnGetOffersAdminSuccess, FOnGetOffersAdminError, FOnGetOffersAdminComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UGetOffersAdminRequest, UGetActiveOffersResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetOffersAdminRequest*, FOnGetOffersAdminSuccess, FOnGetOffersAdminError, FOnGetOffersAdminComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UGetOffersAdminRequest*, TBeamFullResponseHandler<UGetOffersAdminRequest*, UGetActiveOffersResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetOffersAdminRequest*,
                                                                                   TBeamFullResponseHandler<UGetOffersAdminRequest*, UGetActiveOffersResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPostPurchaseRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPostPurchaseRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPostPurchaseRequest, UCommonResponse>(
	const int64&, UPostPurchaseRequest*, FOnPostPurchaseSuccess, FOnPostPurchaseError, FOnPostPurchaseComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPostPurchaseRequest, UCommonResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostPurchaseRequest*, FOnPostPurchaseSuccess, FOnPostPurchaseError, FOnPostPurchaseComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPostPurchaseRequest*, TBeamFullResponseHandler<UPostPurchaseRequest*, UCommonResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostPurchaseRequest*,
                                                                                   TBeamFullResponseHandler<UPostPurchaseRequest*, UCommonResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPutPurchaseRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPutPurchaseRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPutPurchaseRequest, UResultResponse>(
	const int64&, UPutPurchaseRequest*, FOnPutPurchaseSuccess, FOnPutPurchaseError, FOnPutPurchaseComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPutPurchaseRequest, UResultResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPutPurchaseRequest*, FOnPutPurchaseSuccess, FOnPutPurchaseError, FOnPutPurchaseComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPutPurchaseRequest*, TBeamFullResponseHandler<UPutPurchaseRequest*, UResultResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPutPurchaseRequest*,
                                                                                   TBeamFullResponseHandler<UPutPurchaseRequest*, UResultResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UGetListingsRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UGetListingsRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UGetListingsRequest, UActiveListingResponse>(
	const int64&, UGetListingsRequest*, FOnGetListingsSuccess, FOnGetListingsError, FOnGetListingsComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UGetListingsRequest, UActiveListingResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetListingsRequest*, FOnGetListingsSuccess, FOnGetListingsError, FOnGetListingsComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UGetListingsRequest*, TBeamFullResponseHandler<UGetListingsRequest*, UActiveListingResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetListingsRequest*,
                                                                                   TBeamFullResponseHandler<UGetListingsRequest*, UActiveListingResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UDeleteStatusRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UDeleteStatusRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UDeleteStatusRequest, UCommonResponse>(
	const int64&, UDeleteStatusRequest*, FOnDeleteStatusSuccess, FOnDeleteStatusError, FOnDeleteStatusComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UDeleteStatusRequest, UCommonResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UDeleteStatusRequest*, FOnDeleteStatusSuccess, FOnDeleteStatusError, FOnDeleteStatusComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UDeleteStatusRequest*, TBeamFullResponseHandler<UDeleteStatusRequest*, UCommonResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UDeleteStatusRequest*,
                                                                                   TBeamFullResponseHandler<UDeleteStatusRequest*, UCommonResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPostCouponsRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPostCouponsRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPostCouponsRequest, UCommonResponse>(
	const int64&, UPostCouponsRequest*, FOnPostCouponsSuccess, FOnPostCouponsError, FOnPostCouponsComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPostCouponsRequest, UCommonResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostCouponsRequest*, FOnPostCouponsSuccess, FOnPostCouponsError, FOnPostCouponsComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPostCouponsRequest*, TBeamFullResponseHandler<UPostCouponsRequest*, UCommonResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostCouponsRequest*,
                                                                                   TBeamFullResponseHandler<UPostCouponsRequest*, UCommonResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPostStatsUpdateRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPostStatsUpdateRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPostStatsUpdateRequest, UCommonResponse>(
	const int64&, UPostStatsUpdateRequest*, FOnPostStatsUpdateSuccess, FOnPostStatsUpdateError, FOnPostStatsUpdateComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPostStatsUpdateRequest, UCommonResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostStatsUpdateRequest*, FOnPostStatsUpdateSuccess, FOnPostStatsUpdateError, FOnPostStatsUpdateComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPostStatsUpdateRequest*, TBeamFullResponseHandler<UPostStatsUpdateRequest*, UCommonResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostStatsUpdateRequest*,
                                                                                   TBeamFullResponseHandler<UPostStatsUpdateRequest*, UCommonResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UGetOffersRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UGetOffersRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UGetOffersRequest, UGetActiveOffersResponse>(
	const int64&, UGetOffersRequest*, FOnGetOffersSuccess, FOnGetOffersError, FOnGetOffersComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UGetOffersRequest, UGetActiveOffersResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetOffersRequest*, FOnGetOffersSuccess, FOnGetOffersError, FOnGetOffersComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UGetOffersRequest*, TBeamFullResponseHandler<UGetOffersRequest*, UGetActiveOffersResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetOffersRequest*,
                                                                                   TBeamFullResponseHandler<UGetOffersRequest*, UGetActiveOffersResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UObjectCalendarsPostClaimRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UObjectCalendarsPostClaimRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UObjectCalendarsPostClaimRequest, UCommonResponse>(
	const int64&, UObjectCalendarsPostClaimRequest*, FOnObjectCalendarsPostClaimSuccess, FOnObjectCalendarsPostClaimError, FOnObjectCalendarsPostClaimComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UObjectCalendarsPostClaimRequest, UCommonResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UObjectCalendarsPostClaimRequest*, FOnObjectCalendarsPostClaimSuccess, FOnObjectCalendarsPostClaimError, FOnObjectCalendarsPostClaimComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UObjectCalendarsPostClaimRequest*, TBeamFullResponseHandler<UObjectCalendarsPostClaimRequest*, UCommonResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UObjectCalendarsPostClaimRequest*,
                                                                                   TBeamFullResponseHandler<UObjectCalendarsPostClaimRequest*, UCommonResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UGetCalendarsRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UGetCalendarsRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UGetCalendarsRequest, UCalendarQueryResponse>(
	const int64&, UGetCalendarsRequest*, FOnGetCalendarsSuccess, FOnGetCalendarsError, FOnGetCalendarsComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UGetCalendarsRequest, UCalendarQueryResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetCalendarsRequest*, FOnGetCalendarsSuccess, FOnGetCalendarsError, FOnGetCalendarsComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UGetCalendarsRequest*, TBeamFullResponseHandler<UGetCalendarsRequest*, UCalendarQueryResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetCalendarsRequest*,
                                                                                   TBeamFullResponseHandler<UGetCalendarsRequest*, UCalendarQueryResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UGetListTagsRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UGetListTagsRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UGetListTagsRequest, UListTagsResponse>(
	const int64&, UGetListTagsRequest*, FOnGetListTagsSuccess, FOnGetListTagsError, FOnGetListTagsComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UGetListTagsRequest, UListTagsResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetListTagsRequest*, FOnGetListTagsSuccess, FOnGetListTagsError, FOnGetListTagsComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UGetListTagsRequest*, TBeamFullResponseHandler<UGetListTagsRequest*, UListTagsResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetListTagsRequest*,
                                                                                   TBeamFullResponseHandler<UGetListTagsRequest*, UListTagsResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UBasicAnnouncementsGetListRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UBasicAnnouncementsGetListRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UBasicAnnouncementsGetListRequest, UAnnouncementContentResponse>(
	const int64&, UBasicAnnouncementsGetListRequest*, FOnBasicAnnouncementsGetListSuccess, FOnBasicAnnouncementsGetListError, FOnBasicAnnouncementsGetListComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UBasicAnnouncementsGetListRequest, UAnnouncementContentResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UBasicAnnouncementsGetListRequest*, FOnBasicAnnouncementsGetListSuccess, FOnBasicAnnouncementsGetListError, FOnBasicAnnouncementsGetListComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UBasicAnnouncementsGetListRequest*, TBeamFullResponseHandler<UBasicAnnouncementsGetListRequest*, UAnnouncementContentResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UBasicAnnouncementsGetListRequest*,
                                                                                   TBeamFullResponseHandler<UBasicAnnouncementsGetListRequest*, UAnnouncementContentResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UBasicAnnouncementsGetSearchRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UBasicAnnouncementsGetSearchRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UBasicAnnouncementsGetSearchRequest, UAnnouncementContentResponse>(
	const int64&, UBasicAnnouncementsGetSearchRequest*, FOnBasicAnnouncementsGetSearchSuccess, FOnBasicAnnouncementsGetSearchError, FOnBasicAnnouncementsGetSearchComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UBasicAnnouncementsGetSearchRequest, UAnnouncementContentResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UBasicAnnouncementsGetSearchRequest*, FOnBasicAnnouncementsGetSearchSuccess, FOnBasicAnnouncementsGetSearchError, FOnBasicAnnouncementsGetSearchComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UBasicAnnouncementsGetSearchRequest*, TBeamFullResponseHandler<UBasicAnnouncementsGetSearchRequest*, UAnnouncementContentResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UBasicAnnouncementsGetSearchRequest*,
                                                                                   TBeamFullResponseHandler<UBasicAnnouncementsGetSearchRequest*, UAnnouncementContentResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UGetListDefinitionsRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UGetListDefinitionsRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UGetListDefinitionsRequest, UListDefinitionsResponse>(
	const int64&, UGetListDefinitionsRequest*, FOnGetListDefinitionsSuccess, FOnGetListDefinitionsError, FOnGetListDefinitionsComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UGetListDefinitionsRequest, UListDefinitionsResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetListDefinitionsRequest*, FOnGetListDefinitionsSuccess, FOnGetListDefinitionsError, FOnGetListDefinitionsComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UGetListDefinitionsRequest*, TBeamFullResponseHandler<UGetListDefinitionsRequest*, UListDefinitionsResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetListDefinitionsRequest*,
                                                                                   TBeamFullResponseHandler<UGetListDefinitionsRequest*, UListDefinitionsResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPostAnnouncementsRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPostAnnouncementsRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPostAnnouncementsRequest, UEmptyResponse>(
	const int64&, UPostAnnouncementsRequest*, FOnPostAnnouncementsSuccess, FOnPostAnnouncementsError, FOnPostAnnouncementsComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPostAnnouncementsRequest, UEmptyResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostAnnouncementsRequest*, FOnPostAnnouncementsSuccess, FOnPostAnnouncementsError, FOnPostAnnouncementsComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPostAnnouncementsRequest*, TBeamFullResponseHandler<UPostAnnouncementsRequest*, UEmptyResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostAnnouncementsRequest*,
                                                                                   TBeamFullResponseHandler<UPostAnnouncementsRequest*, UEmptyResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UBasicAnnouncementsDeleteAnnouncementsRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UBasicAnnouncementsDeleteAnnouncementsRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UBasicAnnouncementsDeleteAnnouncementsRequest, UEmptyResponse>(
	const int64&, UBasicAnnouncementsDeleteAnnouncementsRequest*, FOnBasicAnnouncementsDeleteAnnouncementsSuccess, FOnBasicAnnouncementsDeleteAnnouncementsError, FOnBasicAnnouncementsDeleteAnnouncementsComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UBasicAnnouncementsDeleteAnnouncementsRequest, UEmptyResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UBasicAnnouncementsDeleteAnnouncementsRequest*, FOnBasicAnnouncementsDeleteAnnouncementsSuccess, FOnBasicAnnouncementsDeleteAnnouncementsError, FOnBasicAnnouncementsDeleteAnnouncementsComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UBasicAnnouncementsDeleteAnnouncementsRequest*, TBeamFullResponseHandler<UBasicAnnouncementsDeleteAnnouncementsRequest*, UEmptyResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UBasicAnnouncementsDeleteAnnouncementsRequest*,
                                                                                   TBeamFullResponseHandler<UBasicAnnouncementsDeleteAnnouncementsRequest*, UEmptyResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UBasicAnnouncementsGetContentRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UBasicAnnouncementsGetContentRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UBasicAnnouncementsGetContentRequest, UAnnouncementContentResponse>(
	const int64&, UBasicAnnouncementsGetContentRequest*, FOnBasicAnnouncementsGetContentSuccess, FOnBasicAnnouncementsGetContentError, FOnBasicAnnouncementsGetContentComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UBasicAnnouncementsGetContentRequest, UAnnouncementContentResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UBasicAnnouncementsGetContentRequest*, FOnBasicAnnouncementsGetContentSuccess, FOnBasicAnnouncementsGetContentError, FOnBasicAnnouncementsGetContentComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UBasicAnnouncementsGetContentRequest*, TBeamFullResponseHandler<UBasicAnnouncementsGetContentRequest*, UAnnouncementContentResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UBasicAnnouncementsGetContentRequest*,
                                                                                   TBeamFullResponseHandler<UBasicAnnouncementsGetContentRequest*, UAnnouncementContentResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPutReadRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPutReadRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPutReadRequest, UCommonResponse>(
	const int64&, UPutReadRequest*, FOnPutReadSuccess, FOnPutReadError, FOnPutReadComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPutReadRequest, UCommonResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPutReadRequest*, FOnPutReadSuccess, FOnPutReadError, FOnPutReadComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPutReadRequest*, TBeamFullResponseHandler<UPutReadRequest*, UCommonResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPutReadRequest*,
                                                                                   TBeamFullResponseHandler<UPutReadRequest*, UCommonResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UObjectAnnouncementsPostClaimRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UObjectAnnouncementsPostClaimRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UObjectAnnouncementsPostClaimRequest, UCommonResponse>(
	const int64&, UObjectAnnouncementsPostClaimRequest*, FOnObjectAnnouncementsPostClaimSuccess, FOnObjectAnnouncementsPostClaimError, FOnObjectAnnouncementsPostClaimComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UObjectAnnouncementsPostClaimRequest, UCommonResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UObjectAnnouncementsPostClaimRequest*, FOnObjectAnnouncementsPostClaimSuccess, FOnObjectAnnouncementsPostClaimError, FOnObjectAnnouncementsPostClaimComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UObjectAnnouncementsPostClaimRequest*, TBeamFullResponseHandler<UObjectAnnouncementsPostClaimRequest*, UCommonResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UObjectAnnouncementsPostClaimRequest*,
                                                                                   TBeamFullResponseHandler<UObjectAnnouncementsPostClaimRequest*, UCommonResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UGetRawRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UGetRawRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UGetRawRequest, UAnnouncementRawResponse>(
	const int64&, UGetRawRequest*, FOnGetRawSuccess, FOnGetRawError, FOnGetRawComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UGetRawRequest, UAnnouncementRawResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetRawRequest*, FOnGetRawSuccess, FOnGetRawError, FOnGetRawComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UGetRawRequest*, TBeamFullResponseHandler<UGetRawRequest*, UAnnouncementRawResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetRawRequest*,
                                                                                   TBeamFullResponseHandler<UGetRawRequest*, UAnnouncementRawResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UGetAnnouncementsRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UGetAnnouncementsRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UGetAnnouncementsRequest, UAnnouncementQueryResponse>(
	const int64&, UGetAnnouncementsRequest*, FOnGetAnnouncementsSuccess, FOnGetAnnouncementsError, FOnGetAnnouncementsComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UGetAnnouncementsRequest, UAnnouncementQueryResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetAnnouncementsRequest*, FOnGetAnnouncementsSuccess, FOnGetAnnouncementsError, FOnGetAnnouncementsComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UGetAnnouncementsRequest*, TBeamFullResponseHandler<UGetAnnouncementsRequest*, UAnnouncementQueryResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetAnnouncementsRequest*,
                                                                                   TBeamFullResponseHandler<UGetAnnouncementsRequest*, UAnnouncementQueryResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UObjectAnnouncementsDeleteAnnouncementsRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UObjectAnnouncementsDeleteAnnouncementsRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UObjectAnnouncementsDeleteAnnouncementsRequest, UCommonResponse>(
	const int64&, UObjectAnnouncementsDeleteAnnouncementsRequest*, FOnObjectAnnouncementsDeleteAnnouncementsSuccess, FOnObjectAnnouncementsDeleteAnnouncementsError, FOnObjectAnnouncementsDeleteAnnouncementsComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UObjectAnnouncementsDeleteAnnouncementsRequest, UCommonResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UObjectAnnouncementsDeleteAnnouncementsRequest*, FOnObjectAnnouncementsDeleteAnnouncementsSuccess, FOnObjectAnnouncementsDeleteAnnouncementsError, FOnObjectAnnouncementsDeleteAnnouncementsComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UObjectAnnouncementsDeleteAnnouncementsRequest*, TBeamFullResponseHandler<UObjectAnnouncementsDeleteAnnouncementsRequest*, UCommonResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UObjectAnnouncementsDeleteAnnouncementsRequest*,
                                                                                   TBeamFullResponseHandler<UObjectAnnouncementsDeleteAnnouncementsRequest*, UCommonResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UGetTemplateRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UGetTemplateRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UGetTemplateRequest, UMailTemplate>(
	const int64&, UGetTemplateRequest*, FOnGetTemplateSuccess, FOnGetTemplateError, FOnGetTemplateComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UGetTemplateRequest, UMailTemplate>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetTemplateRequest*, FOnGetTemplateSuccess, FOnGetTemplateError, FOnGetTemplateComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UGetTemplateRequest*, TBeamFullResponseHandler<UGetTemplateRequest*, UMailTemplate*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetTemplateRequest*,
                                                                                   TBeamFullResponseHandler<UGetTemplateRequest*, UMailTemplate*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UBasicMailGetMailRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UBasicMailGetMailRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UBasicMailGetMailRequest, UMailResponse>(
	const int64&, UBasicMailGetMailRequest*, FOnBasicMailGetMailSuccess, FOnBasicMailGetMailError, FOnBasicMailGetMailComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UBasicMailGetMailRequest, UMailResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UBasicMailGetMailRequest*, FOnBasicMailGetMailSuccess, FOnBasicMailGetMailError, FOnBasicMailGetMailComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UBasicMailGetMailRequest*, TBeamFullResponseHandler<UBasicMailGetMailRequest*, UMailResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UBasicMailGetMailRequest*,
                                                                                   TBeamFullResponseHandler<UBasicMailGetMailRequest*, UMailResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UGetDetailRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UGetDetailRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UGetDetailRequest, UMailResponse>(
	const int64&, UGetDetailRequest*, FOnGetDetailSuccess, FOnGetDetailError, FOnGetDetailComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UGetDetailRequest, UMailResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetDetailRequest*, FOnGetDetailSuccess, FOnGetDetailError, FOnGetDetailComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UGetDetailRequest*, TBeamFullResponseHandler<UGetDetailRequest*, UMailResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetDetailRequest*,
                                                                                   TBeamFullResponseHandler<UGetDetailRequest*, UMailResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UGetCategoriesRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UGetCategoriesRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UGetCategoriesRequest, UListMailCategoriesResponse>(
	const int64&, UGetCategoriesRequest*, FOnGetCategoriesSuccess, FOnGetCategoriesError, FOnGetCategoriesComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UGetCategoriesRequest, UListMailCategoriesResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetCategoriesRequest*, FOnGetCategoriesSuccess, FOnGetCategoriesError, FOnGetCategoriesComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UGetCategoriesRequest*, TBeamFullResponseHandler<UGetCategoriesRequest*, UListMailCategoriesResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UGetCategoriesRequest*,
                                                                                   TBeamFullResponseHandler<UGetCategoriesRequest*, UListMailCategoriesResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UObjectMailPostSearchRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UObjectMailPostSearchRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UObjectMailPostSearchRequest, UMailSearchResponse>(
	const int64&, UObjectMailPostSearchRequest*, FOnObjectMailPostSearchSuccess, FOnObjectMailPostSearchError, FOnObjectMailPostSearchComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UObjectMailPostSearchRequest, UMailSearchResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UObjectMailPostSearchRequest*, FOnObjectMailPostSearchSuccess, FOnObjectMailPostSearchError, FOnObjectMailPostSearchComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UObjectMailPostSearchRequest*, TBeamFullResponseHandler<UObjectMailPostSearchRequest*, UMailSearchResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UObjectMailPostSearchRequest*,
                                                                                   TBeamFullResponseHandler<UObjectMailPostSearchRequest*, UMailSearchResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPutBulkRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPutBulkRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPutBulkRequest, UMailSuccessResponse>(
	const int64&, UPutBulkRequest*, FOnPutBulkSuccess, FOnPutBulkError, FOnPutBulkComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPutBulkRequest, UMailSuccessResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPutBulkRequest*, FOnPutBulkSuccess, FOnPutBulkError, FOnPutBulkComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPutBulkRequest*, TBeamFullResponseHandler<UPutBulkRequest*, UMailSuccessResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPutBulkRequest*,
                                                                                   TBeamFullResponseHandler<UPutBulkRequest*, UMailSuccessResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPutAcceptManyRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPutAcceptManyRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPutAcceptManyRequest, UMailSuccessResponse>(
	const int64&, UPutAcceptManyRequest*, FOnPutAcceptManySuccess, FOnPutAcceptManyError, FOnPutAcceptManyComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPutAcceptManyRequest, UMailSuccessResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPutAcceptManyRequest*, FOnPutAcceptManySuccess, FOnPutAcceptManyError, FOnPutAcceptManyComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPutAcceptManyRequest*, TBeamFullResponseHandler<UPutAcceptManyRequest*, UMailSuccessResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPutAcceptManyRequest*,
                                                                                   TBeamFullResponseHandler<UPutAcceptManyRequest*, UMailSuccessResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UObjectMailGetMailRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UObjectMailGetMailRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UObjectMailGetMailRequest, UMailQueryResponse>(
	const int64&, UObjectMailGetMailRequest*, FOnObjectMailGetMailSuccess, FOnObjectMailGetMailError, FOnObjectMailGetMailComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UObjectMailGetMailRequest, UMailQueryResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UObjectMailGetMailRequest*, FOnObjectMailGetMailSuccess, FOnObjectMailGetMailError, FOnObjectMailGetMailComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UObjectMailGetMailRequest*, TBeamFullResponseHandler<UObjectMailGetMailRequest*, UMailQueryResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UObjectMailGetMailRequest*,
                                                                                   TBeamFullResponseHandler<UObjectMailGetMailRequest*, UMailQueryResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UObjectMailPutMailRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UObjectMailPutMailRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UObjectMailPutMailRequest, UMailSuccessResponse>(
	const int64&, UObjectMailPutMailRequest*, FOnObjectMailPutMailSuccess, FOnObjectMailPutMailError, FOnObjectMailPutMailComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UObjectMailPutMailRequest, UMailSuccessResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UObjectMailPutMailRequest*, FOnObjectMailPutMailSuccess, FOnObjectMailPutMailError, FOnObjectMailPutMailComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UObjectMailPutMailRequest*, TBeamFullResponseHandler<UObjectMailPutMailRequest*, UMailSuccessResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UObjectMailPutMailRequest*,
                                                                                   TBeamFullResponseHandler<UObjectMailPutMailRequest*, UMailSuccessResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPutAttachmentsRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPutAttachmentsRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPutAttachmentsRequest, UMailSuccessResponse>(
	const int64&, UPutAttachmentsRequest*, FOnPutAttachmentsSuccess, FOnPutAttachmentsError, FOnPutAttachmentsComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPutAttachmentsRequest, UMailSuccessResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPutAttachmentsRequest*, FOnPutAttachmentsSuccess, FOnPutAttachmentsError, FOnPutAttachmentsComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPutAttachmentsRequest*, TBeamFullResponseHandler<UPutAttachmentsRequest*, UMailSuccessResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPutAttachmentsRequest*,
                                                                                   TBeamFullResponseHandler<UPutAttachmentsRequest*, UMailSuccessResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UBasicMailPutMailRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UBasicMailPutMailRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UBasicMailPutMailRequest, UMailSuccessResponse>(
	const int64&, UBasicMailPutMailRequest*, FOnBasicMailPutMailSuccess, FOnBasicMailPutMailError, FOnBasicMailPutMailComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UBasicMailPutMailRequest, UMailSuccessResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UBasicMailPutMailRequest*, FOnBasicMailPutMailSuccess, FOnBasicMailPutMailError, FOnBasicMailPutMailComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UBasicMailPutMailRequest*, TBeamFullResponseHandler<UBasicMailPutMailRequest*, UMailSuccessResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UBasicMailPutMailRequest*,
                                                                                   TBeamFullResponseHandler<UBasicMailPutMailRequest*, UMailSuccessResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UBasicMailPostBulkRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UBasicMailPostBulkRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UBasicMailPostBulkRequest, UMailSuccessResponse>(
	const int64&, UBasicMailPostBulkRequest*, FOnBasicMailPostBulkSuccess, FOnBasicMailPostBulkError, FOnBasicMailPostBulkComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UBasicMailPostBulkRequest, UMailSuccessResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UBasicMailPostBulkRequest*, FOnBasicMailPostBulkSuccess, FOnBasicMailPostBulkError, FOnBasicMailPostBulkComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UBasicMailPostBulkRequest*, TBeamFullResponseHandler<UBasicMailPostBulkRequest*, UMailSuccessResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UBasicMailPostBulkRequest*,
                                                                                   TBeamFullResponseHandler<UBasicMailPostBulkRequest*, UMailSuccessResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UObjectMailPostBulkRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UObjectMailPostBulkRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UObjectMailPostBulkRequest, UMailSuccessResponse>(
	const int64&, UObjectMailPostBulkRequest*, FOnObjectMailPostBulkSuccess, FOnObjectMailPostBulkError, FOnObjectMailPostBulkComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UObjectMailPostBulkRequest, UMailSuccessResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UObjectMailPostBulkRequest*, FOnObjectMailPostBulkSuccess, FOnObjectMailPostBulkError, FOnObjectMailPostBulkComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UObjectMailPostBulkRequest*, TBeamFullResponseHandler<UObjectMailPostBulkRequest*, UMailSuccessResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UObjectMailPostBulkRequest*,
                                                                                   TBeamFullResponseHandler<UObjectMailPostBulkRequest*, UMailSuccessResponse*>);



template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UPostMailRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UPostMailRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UPostMailRequest, USendMailResponse>(
	const int64&, UPostMailRequest*, FOnPostMailSuccess, FOnPostMailError, FOnPostMailComplete);

template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UPostMailRequest, USendMailResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostMailRequest*, FOnPostMailSuccess, FOnPostMailError, FOnPostMailComplete);

template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UPostMailRequest*, TBeamFullResponseHandler<UPostMailRequest*, USendMailResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UPostMailRequest*,
                                                                                   TBeamFullResponseHandler<UPostMailRequest*, USendMailResponse*>);

